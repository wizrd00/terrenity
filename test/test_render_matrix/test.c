#include "unity.h"
#include "terrenity.h"
#include <stdio.h>

static matrix_t mx;

void setUp(void)
{
	mx_init(&mx, false, true);
	return;
}

void tearDown(void)
{
	mx_deinit(&mx);
	return;
}

void test_fill(void)
{
	status_t _stat = SUCCESS;
	pixel_t px = {.ulbd = UNDERLINE | BOLD, .bgnd = LBGBLACK, .fgnd = LFGPURPLE, .cval = 'A'};
	_stat = mx_fill(&mx, &px);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	_stat = mx_render(&mx);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_fill);
	return UNITY_END();
}
