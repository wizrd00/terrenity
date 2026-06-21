#include "unity.h"
#include "terrenity.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

#define ESC '\x1b'

typedef enum {UP, DOWN, RIGHT, LEFT, ANY, QUIT} arrow_t;

static matrix_t mx;

void setUp(void)
{
	status_t _stat = SUCCESS;
	struct winsize ws;
	ioctl(fileno(stdout), TIOCGWINSZ, &ws);
	mx.row = ws.ws_row;
	mx.col = ws.ws_col;
	if ((_stat = mx_init(&mx, true, true)) != SUCCESS)
		fprintf(stderr, "mx_init() failed\nstatus = %d\n", _stat);
	return;
}

void tearDown(void)
{
	mx_deinit(&mx);
	return;
}

static void get_arrow(arrow_t *key)
{
	status_t _stat = SUCCESS;
	unsigned char tmp_key[3];
	for (int i = 0; i < 3; i++) {
		_stat = mx_readkey(tmp_key + i, 1000);
		if (tmp_key[i] == 'q') {
			*key = QUIT;
			return;
		}
		if (_stat == ERRREAD) {
			*key = ANY;
			return;
		}
	}
	if ((tmp_key[0] != ESC) || (tmp_key[1] != '[')) {
		*key = ANY;
		return;
	}
	switch (tmp_key[2]) {
	case 'A' :
		*key = UP; break;
	case 'B' :
		*key = DOWN; break;
	case 'C' :
		*key = RIGHT; break;
	case 'D' :
		*key = LEFT; break;
	default :
		*key = ANY;
	}
	return;
}

void test_moving_shape(void)
{
	status_t _stat = SUCCESS;
	object_t *hdl0;
	object_t *hdl1;
	object_t frame = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = LBGRED,
			.fgnd = LFGRED,
			.cval = ' '
		},
		.active = true,
		.fill = false,
		.x = 0,
		.y = 0,
		.len = mx.col,
		.wid = mx.row
	};
	object_t ship = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = HBGYELLOW,
			.fgnd = LFGYELLOW,
			.cval = ' '
		},
		.active = true,
		.fill =  true,
		.x = (mx.col / 2),
		.y = (mx.row / 2),
		.len = 2,
		.wid = 1,
	};
	_stat = mx_fill(&mx, &(pixel_t){.ulbd = NONE, .bgnd = LBGBLACK, .fgnd = LFGBLACK, .cval = ' '});
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &frame, &hdl0);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &ship, &hdl1);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	TEST_ASSERT_EQUAL(SUCCESS, mx_hide_cursor());

	arrow_t key = ANY;
	while (true) {
		_stat = mx_render(&mx, NULL);
		TEST_ASSERT_EQUAL(SUCCESS, _stat);
		get_arrow(&key);
		switch (key) {
		case UP :
			hdl1->y--;
			break;
		case DOWN :
			hdl1->y++;
			break;
		case RIGHT :
			hdl1->x++;
			break;
		case LEFT :
			hdl1->x--;
			break;
		case QUIT :
			mx_show_cursor();
			return;
		}
		if (key != ANY) {
			mx_clear();
			mx_fill(&mx, &(pixel_t){.ulbd = NONE, .bgnd = LBGBLACK, .fgnd = LFGBLACK, .cval = ' '});
			mx_refresh(&mx);
		}
	}
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_moving_shape);
	return UNITY_END();
}
