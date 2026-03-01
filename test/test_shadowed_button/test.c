#include "unity.h"
#include "terrenity.h"

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
void test(void)
{
	status_t _stat = SUCCESS;
	object_t sun = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = BLINK,
			.bgnd = HBGYELLOW,
			.fgnd = LFGYELLOW,
			.cval = '~'
		},
		.active = true,
		.fill = true,
		.x = mx.col - 10,
		.y = 2,
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
		.x = mx.col / 2 - 10,
		.y = mx.row / 2 - 4,
		.len = 10,
		.wid = 4
	};
	object_t button = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = NONE,
			.bgnd = LBGWHITE,
			.fgnd = LFGWHITE,
			.cval = ' '
		},
		.active = true,
		.fill = true,
		.x = mx.col / 2 - 9,
		.y = mx.row / 2 - 5,
		.len = 10,
		.wid = 4
	};
	object_t *handle0;
	object_t *handle1;
	object_t *handle2;

	_stat = mx_fill(&mx, &(pixel_t){.ulbd = NONE, .bgnd = HBGBLUE, .fgnd = HFGBLUE, .cval = ' '});
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_refresh(&mx);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &sun, &handle0);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &shadow, &handle1);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &button, &handle2);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_render(&mx);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test);
	return UNITY_END();
}
