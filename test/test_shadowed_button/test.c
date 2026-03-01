#include "unity.h"
#include "terrenity.h"

#define PIXELING(val) &(pixel_t){.ulbd = NONE, .bgnd = LBGWHITE, .fgnd = LFGBLACK, .cval = val}

matrix_t mx;

void setUp(void)
{
	struct winsize ws;
	ioctl(fileno(stdout), TIOCGWINSZ, &ws);
	mx.row = ws.ws_row;
	mx.col = ws.ws_col;
	if (mx_init(&mx, true, true) != SUCCESS)
		fprintf(stderr, "mx_init() failed");
	mx_clear();
	return;
}

void tearDown(void)
{
	mx_deinit(&mx);
	return;
}

status_t add_text(matrix_t *restrict mtx)
{
	mx_setpixel(mtx, PIXELING('h'), mx.col / 2 - 30, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('e'), mx.col / 2 - 29, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('l'), mx.col / 2 - 28, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('l'), mx.col / 2 - 27, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('o'), mx.col / 2 - 26, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING(' '), mx.col / 2 - 25, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING('w'), mx.col / 2 - 24, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('o'), mx.col / 2 - 23, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('r'), mx.col / 2 - 22, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('l'), mx.col / 2 - 21, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('d'), mx.col / 2 - 20, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING(' '), mx.col / 2 - 19, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING('f'), mx.col / 2 - 18, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('r'), mx.col / 2 - 17, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('o'), mx.col / 2 - 16, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('m'), mx.col / 2 - 15, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING(' '), mx.col / 2 - 14, mx.row / 2 - 4);

	mx_setpixel(mtx, PIXELING('t'), mx.col / 2 - 13, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('e'), mx.col / 2 - 12, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('r'), mx.col / 2 - 11, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('r'), mx.col / 2 - 10, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('e'), mx.col / 2 - 9, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('n'), mx.col / 2 - 8, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('i'), mx.col / 2 - 7, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('n'), mx.col / 2 - 6, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('t'), mx.col / 2 - 5, mx.row / 2 - 4);
	mx_setpixel(mtx, PIXELING('y'), mx.col / 2 - 4, mx.row / 2 - 4);
	mx_refresh(mtx);
	mx_refresh(mtx);
	return SUCCESS;
}

void test(void)
{
	status_t _stat = SUCCESS;
	object_t sun = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = HBGYELLOW,
			.fgnd = LFGBLACK,
			.cval = ' '
		},
		.active = true,
		.fill = true,
		.x = mx.col - 20,
		.y = 3,
		.len = 8,
		.wid = 4
	};
	object_t shadow = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = LBGBLACK,
			.fgnd = LFGBLACK,
			.cval = ' '
		},
		.active = true,
		.fill = true,
		.x = mx.col / 2 - 32,
		.y = mx.row / 2 - 5,
		.len = 32,
		.wid = 5
	};
	object_t button = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = LBGWHITE,
			.fgnd = LFGBLACK,
			.cval = ' '
		},
		.active = true,
		.fill = true,
		.x = mx.col / 2 - 31,
		.y = mx.row / 2 - 6,
		.len = 32,
		.wid = 5
	};
	object_t *handle0;
	object_t *handle1;
	object_t *handle2;

	_stat = mx_fill(&mx, &(pixel_t){.ulbd = NONE, .bgnd = HBGBLUE, .fgnd = LFGBLACK, .cval = ' '});
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_refresh(&mx);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &sun, &handle0);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &shadow, &handle1);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &button, &handle2);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_render(&mx, add_text);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test);
	return UNITY_END();
}
