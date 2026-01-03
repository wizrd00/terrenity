#include "unity.h"
#include "tool/draw.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pixel_t **src_mx0;

void setUp(void)
{
	pixel_t p = {0, 0, 0, 0};
	src_mx0 = (pixel_t **) malloc(sizeof (pixel_t *) * 9);
	for (int i = 0; i < 9; i++) {
		src_mx0[i] = (pixel_t *) malloc(sizeof (pixel_t) * 16);
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			src_mx0[i][j] = p;
		}
	}
	return;
}

void tearDown(void)
{
	for (int i = 0; i < 9; i++)
		free(src_mx0[i]);
	free(src_mx0);
	return;
}

void test_draw_shape_rectangle0(void)
{
	matrix_t mx = {.float_mx = src_mx0, .row = 9, .col = 16};
	pixel_t zeropixel = {0, 0, 0, 0};
	object_t obj = {
		.shape = RECTANGLE,
		.pixel = {0, 0, 0, 1},
		.fill = 0,
		.len = 8,
		.wid = 5,
		.x = 2,
		.y = 3
	};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++)
			printf("%lu ", src_mx0[i][j]);
		printf("\n");
	}
	TEST_ASSERT_EQUAL(SUCCESS, draw_shape_rectangle(&mx, &obj));
	printf("\n\n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			unsigned int x = src_mx0[i][j].cval;
			src_mx0[i][j] = zeropixel;
			printf("%u ", x);
		}
		printf("\n");
	} 
	printf("\n\n");
	return;
}

void test_draw_shape_rectangle1(void)
{
	matrix_t mx = {.float_mx = src_mx0, .row = 9, .col = 16};
	pixel_t zeropixel = {0, 0, 0, 0};
	object_t obj = {
		.shape = RECTANGLE,
		.pixel = {0, 0, 0, 1},
		.fill = 0,
		.len = 5,
		.wid = 5,
		.x = 2,
		.y = 5
	};
	TEST_ASSERT_EQUAL(BADSIZE, draw_shape_rectangle(&mx, &obj));
	return;
}

void test_draw_shape_rhombus0(void)
{
	matrix_t mx = {.float_mx = src_mx0, .row = 9, .col = 16};
	pixel_t zeropixel = {0, 0, 0, 0};
	object_t obj = {
		.shape = RHOMBUS,
		.pixel = {0, 0, 0, 1},
		.fill = 0,
		.len = 4,
		.wid = 4,
		.x = 4,
		.y = 1
	};
	printf("\n\n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++)
			printf("%lu ", src_mx0[i][j]);
		printf("\n");
	}
	TEST_ASSERT_EQUAL(SUCCESS, draw_shape_rhombus(&mx, &obj));
	printf("\n\n");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 16; j++) {
			unsigned int x = src_mx0[i][j].cval;
			src_mx0[i][j] = zeropixel;
			printf("%u ", x);
		}
		printf("\n");
	} 
	printf("\n\n");
	return;
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_draw_shape_rectangle0);
	RUN_TEST(test_draw_shape_rectangle1);
	RUN_TEST(test_draw_shape_rhombus0);
	return UNITY_END();
}
