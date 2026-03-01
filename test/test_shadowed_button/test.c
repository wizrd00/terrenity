#include "unity.h"
#include "terrenity.h"

void setUp(void)
{
	struct winsize ws;
	ioctl(fileno(stdout), TIOCGWINSZ, &ws);
	mx.row = ws.ws_row;
	mx.col = ws.ws_col;
	if (mx_init(&mx, true, true) != SUCCESS)
		fprintf(stderr, "mx_init() failed");
	return;
}

void tearDown(void)
{
	mx_deinit(&mx);
	return;
}

void test_fill_screen(void)
{
	status_t _stat = SUCCESS;
	_stat = mx_fill(&mx, &(pixel_t){.ulbd = NONE, .bgnd = HBGBLUE, .fgnd = HFGBLUE, .cval = ' '});
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_refresh(&mx);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
}

void test_button(void)
{

}

int main(void) {
	UNITY_BEGIN();
	return UNITY_END();
}
