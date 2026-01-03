#include "unity.h"
#include "terrenity.h"
#include <stdio.h>

static matrix_t mx;

void setUp(void)
{
	mx_init(&mx, true, true);
	return;
}

void tearDown(void)
{
	mx_deinit(&mx);
	return;
}

void test_readkey(void)
{
	status_t _stat = SUCCESS;
	unsigned char key;
	_stat = mx_readkey(&key, 10);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	putchar(key);
	fflush(stdout);
	_stat = mx_readkey(&key, 30);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	putchar(key);
	putchar('\n');
	fflush(stdout);
	return;
}

void test_readline(void)
{
	status_t _stat = SUCCESS;
	char line[8];
	_stat = mx_readline(line, 8);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_readkey);
	RUN_TEST(test_readline);
	return UNITY_END();
}
