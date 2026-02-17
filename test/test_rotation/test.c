#include "unity.h"
#include "tool/rotation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **dst_mx0;
char **src_mx0;
char **dst_mx1;
char **src_mx1;

void setUp(void)
{
	char r0[] = {'a', 'b', 'c', 'd'};
	char r1[] = {'x', 'y', 'z', 't'};
	char r2[] = {'i', 'j', 'k', 'l'};
	char r3[] = {'e', 'f', 'g', 'h'};
	char r4[] = {'a', 'b', 'c', 'd', 'e'};
	char r5[] = {'i', 'j', 'k', 'l', 'm'};
	char r6[] = {'f', 'g', 'h', 'o', 'p'};
	char r7[] = {'v', 'w', 'x', 'y', 'z'};
	char r8[] = {'q', 'r', 's', 't', 'u'};
	dst_mx0 = (char **) calloc(4, sizeof(char *));
	src_mx0 = (char **) calloc(4, sizeof(char *));
	for (int i = 0; i < 4; i++) {
		dst_mx0[i] = (char *) calloc(4, sizeof(char));
		src_mx0[i] = (char *) calloc(4, sizeof(char));
	}
	memcpy(src_mx0[0], r0, 4);
	memcpy(src_mx0[1], r1, 4);
	memcpy(src_mx0[2], r2, 4);
	memcpy(src_mx0[3], r3, 4);
	dst_mx1 = (char **) calloc(5, sizeof(char *));
	src_mx1 = (char **) calloc(5, sizeof(char *));
	for (int i = 0; i < 5; i++) {
		dst_mx1[i] = (char *) calloc(5, sizeof(char));
		src_mx1[i] = (char *) calloc(5, sizeof(char));
	}
	memcpy(src_mx1[0], r4, 5);
	memcpy(src_mx1[1], r5, 5);
	memcpy(src_mx1[2], r6, 5);
	memcpy(src_mx1[3], r7, 5);
	memcpy(src_mx1[4], r8, 5);
	return;
}

void tearDown(void)
{
	for (size_t i = 0; i < 4; i++) {
		free(dst_mx0[i]);
		free(src_mx0[i]);
	}
	free(dst_mx0);
	free(src_mx0);
	for (size_t i = 0; i < 5; i++) {
		free(dst_mx1[i]);
		free(src_mx1[i]);
	}
	free(dst_mx1);
	free(src_mx1);
	return;
}

void test_rotate_quarter_right(void)
{
	// I temporary change arguments type to char just for testing
	rotate_quarter_right(src_mx0, dst_mx0, 4);
	rotate_quarter_right(src_mx1, dst_mx1, 5);	
	printf("%c %c %c %c\n", src_mx0[0][0], src_mx0[0][1], src_mx0[0][2], src_mx0[0][3]);
	printf("%c %c %c %c\n", src_mx0[1][0], src_mx0[1][1], src_mx0[1][2], src_mx0[1][3]);
	printf("%c %c %c %c\n", src_mx0[2][0], src_mx0[2][1], src_mx0[2][2], src_mx0[2][3]);
	printf("%c %c %c %c\n\n", src_mx0[3][0], src_mx0[3][1], src_mx0[3][2], src_mx0[3][3]);

	printf("%c %c %c %c\n", dst_mx0[0][0], dst_mx0[0][1], dst_mx0[0][2], dst_mx0[0][3]);
	printf("%c %c %c %c\n", dst_mx0[1][0], dst_mx0[1][1], dst_mx0[1][2], dst_mx0[1][3]);
	printf("%c %c %c %c\n", dst_mx0[2][0], dst_mx0[2][1], dst_mx0[2][2], dst_mx0[2][3]);
	printf("%c %c %c %c\n\n", dst_mx0[3][0], dst_mx0[3][1], dst_mx0[3][2], dst_mx0[3][3]);

	printf("%c %c %c %c %c\n", src_mx1[0][0], src_mx1[0][1], src_mx1[0][2], src_mx1[0][3], src_mx1[0][4]);
	printf("%c %c %c %c %c\n", src_mx1[1][0], src_mx1[1][1], src_mx1[1][2], src_mx1[1][3], src_mx1[1][4]);
	printf("%c %c %c %c %c\n", src_mx1[2][0], src_mx1[2][1], src_mx1[2][2], src_mx1[2][3], src_mx1[2][4]);
	printf("%c %c %c %c %c\n", src_mx1[3][0], src_mx1[3][1], src_mx1[3][2], src_mx1[3][3], src_mx1[3][4]);
	printf("%c %c %c %c %c\n\n", src_mx1[4][0], src_mx1[4][1], src_mx1[4][2], src_mx1[4][3], src_mx1[4][4]);

	printf("%c %c %c %c %c\n", dst_mx1[0][0], dst_mx1[0][1], dst_mx1[0][2], dst_mx1[0][3], dst_mx1[0][4]);
	printf("%c %c %c %c %c\n", dst_mx1[1][0], dst_mx1[1][1], dst_mx1[1][2], dst_mx1[1][3], dst_mx1[1][4]);
	printf("%c %c %c %c %c\n", dst_mx1[2][0], dst_mx1[2][1], dst_mx1[2][2], dst_mx1[2][3], dst_mx1[2][4]);
	printf("%c %c %c %c %c\n", dst_mx1[3][0], dst_mx1[3][1], dst_mx1[3][2], dst_mx1[3][3], dst_mx1[3][4]);
	printf("%c %c %c %c %c\n\n", dst_mx1[4][0], dst_mx1[4][1], dst_mx1[4][2], dst_mx1[4][3], dst_mx1[4][4]);
	TEST_ASSERT_EQUAL('y', fgetc(stdin));
	return;
}

void test_rotate_quarter_left(void)
{
	// I temporary change arguments type to char just for testing
	rotate_quarter_left(src_mx0, dst_mx0, 4);
	rotate_quarter_left(src_mx1, dst_mx1, 5);	
	printf("%c %c %c %c\n", src_mx0[0][0], src_mx0[0][1], src_mx0[0][2], src_mx0[0][3]);
	printf("%c %c %c %c\n", src_mx0[1][0], src_mx0[1][1], src_mx0[1][2], src_mx0[1][3]);
	printf("%c %c %c %c\n", src_mx0[2][0], src_mx0[2][1], src_mx0[2][2], src_mx0[2][3]);
	printf("%c %c %c %c\n\n", src_mx0[3][0], src_mx0[3][1], src_mx0[3][2], src_mx0[3][3]);

	printf("%c %c %c %c\n", dst_mx0[0][0], dst_mx0[0][1], dst_mx0[0][2], dst_mx0[0][3]);
	printf("%c %c %c %c\n", dst_mx0[1][0], dst_mx0[1][1], dst_mx0[1][2], dst_mx0[1][3]);
	printf("%c %c %c %c\n", dst_mx0[2][0], dst_mx0[2][1], dst_mx0[2][2], dst_mx0[2][3]);
	printf("%c %c %c %c\n\n", dst_mx0[3][0], dst_mx0[3][1], dst_mx0[3][2], dst_mx0[3][3]);

	printf("%c %c %c %c %c\n", src_mx1[0][0], src_mx1[0][1], src_mx1[0][2], src_mx1[0][3], src_mx1[0][4]);
	printf("%c %c %c %c %c\n", src_mx1[1][0], src_mx1[1][1], src_mx1[1][2], src_mx1[1][3], src_mx1[1][4]);
	printf("%c %c %c %c %c\n", src_mx1[2][0], src_mx1[2][1], src_mx1[2][2], src_mx1[2][3], src_mx1[2][4]);
	printf("%c %c %c %c %c\n", src_mx1[3][0], src_mx1[3][1], src_mx1[3][2], src_mx1[3][3], src_mx1[3][4]);
	printf("%c %c %c %c %c\n\n", src_mx1[4][0], src_mx1[4][1], src_mx1[4][2], src_mx1[4][3], src_mx1[4][4]);

	printf("%c %c %c %c %c\n", dst_mx1[0][0], dst_mx1[0][1], dst_mx1[0][2], dst_mx1[0][3], dst_mx1[0][4]);
	printf("%c %c %c %c %c\n", dst_mx1[1][0], dst_mx1[1][1], dst_mx1[1][2], dst_mx1[1][3], dst_mx1[1][4]);
	printf("%c %c %c %c %c\n", dst_mx1[2][0], dst_mx1[2][1], dst_mx1[2][2], dst_mx1[2][3], dst_mx1[2][4]);
	printf("%c %c %c %c %c\n", dst_mx1[3][0], dst_mx1[3][1], dst_mx1[3][2], dst_mx1[3][3], dst_mx1[3][4]);
	printf("%c %c %c %c %c\n\n", dst_mx1[4][0], dst_mx1[4][1], dst_mx1[4][2], dst_mx1[4][3], dst_mx1[4][4]);
	fgetc(stdin);
	TEST_ASSERT_EQUAL('y', fgetc(stdin));
	return;
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_rotate_quarter_right);
	RUN_TEST(test_rotate_quarter_left);
	return UNITY_END();
}
