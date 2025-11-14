#include "unity.h"
#include "tool/rotation.h"

void setUp(void) {}

void tearDown(void) {}

void test_rotate_quarter_right(void) {
	char dst_mx0[3][3];
	char src_mx0[3][3] = {
		{'a', 'b', 'c'},
		{'x', 'y', 'z'},
		{'i', 'j', 'k'}
	};
	char dst_mx1[4][4];
	char src_mx1[4][4] = {
		{'a', 'b', 'c', 'd'},
		{'x', 'y', 'z', 't'},
		{'i', 'j', 'k', 'l'},
		{'e', 'f', 'g', 'h'}
	};
	char dst_mx2[5][5];
	char src_mx2[5][5] = {
		{'a', 'b', 'c', 'd', 'e'},
		{'i', 'j', 'k', 'l', 'm'},
		{'f', 'g', 'h', 'o', 'p'},
		{'v', 'w', 'x', 'y', 'z'},
		{'q', 'r', 's', 't', 'u'},
	};
	rotate_quarter_right(src_mx0, dst_mx0, 3);	
	rotate_quarter_right(src_mx1, dst_mx1, 4);	
	rotate_quarter_right(src_mx2, dst_mx2, 5);	
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_rotate_quarter_right);
	return UNITY_END();
}
