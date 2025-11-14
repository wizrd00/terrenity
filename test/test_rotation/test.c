#include "unity.h"
#include "tool/rotation.h"
#include <stdlib.h>
#include <string.h>

char **dst_mx0;
char **src_mx0;
char **dst_mx1;
char **src_mx1;

void setUp(void) {
	char r0[] = {'a', 'b', 'c', 'd'};
	char r1[] = {'x', 'y', 'z', 't'};
	char r2[] = {'i', 'j', 'k', 'l'};
	char r3[] = {'e', 'f', 'g', 'h'};
	char r4[] = {'a', 'b', 'c', 'd', 'e'};
	char r5[] = {'i', 'j', 'k', 'l', 'm'};
	char r6[] = {'f', 'g', 'h', 'o', 'p'};
	char r7[] = {'v', 'w', 'x', 'y', 'z'};
	char r8[] = {'q', 'r', 's', 't', 'u'};
	dst_mx0 = (char **) malloc(sizeof (char *) * 4);
	src_mx0 = (char **) malloc(sizeof (char *) * 4);
	for (int i = 0; i < 4; i++) {
		dst_mx0[i] = (char *) malloc(sizeof (char) * 4);
		src_mx0[i] = (char *) malloc(sizeof (char) * 4);
	}
	memcpy(src_mx0[0], r0, 4);
	memcpy(src_mx0[1], r1, 4);
	memcpy(src_mx0[2], r2, 4);
	memcpy(src_mx0[3], r3, 4);
	dst_mx1 = (char **) malloc(sizeof (char *) * 5);
	src_mx1 = (char **) malloc(sizeof (char *) * 5);
	for (int i = 0; i < 5; i++) {
		dst_mx1[i] = (char *) malloc(sizeof (char) * 5);
		src_mx1[i] = (char *) malloc(sizeof (char) * 5);
	}
	memcpy(src_mx1[0], r4, 5);
	memcpy(src_mx1[1], r5, 5);
	memcpy(src_mx1[2], r6, 5);
	memcpy(src_mx1[3], r7, 5);
	memcpy(src_mx1[4], r8, 5);
	return;
}

void tearDown(void) {
	for (int i = 4; i < 4; i++) {
		free(dst_mx0[i]);
		free(src_mx0[i]);
	}
	free(dst_mx0);
	free(src_mx0);
	for (int i = 5; i < 5; i++) {
		free(dst_mx1[i]);
		free(src_mx1[i]);
	}
	free(dst_mx1);
	free(src_mx1);
	return;
}

void test_rotate_quarter_right(void) {
	rotate_quarter_right((pixel_t **) src_mx0, (pixel_t **) dst_mx0, 4);	
	rotate_quarter_right((pixel_t **) src_mx1, (pixel_t **) dst_mx1, 5);	
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_rotate_quarter_right);
	return UNITY_END();
}
