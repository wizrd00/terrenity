#include "unity.h"
#include "terrenity.h"
#include <stdio.h>
#include <time.h>

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

void test_popup(void)
{
	status_t _stat;
	object_t obj0 = {
		.shape = RECTANGLE,
		.pixel = {
			.ulbd = BOLD,
			.bgnd = LBGRED,
			.fgnd = LFGRED,
			.cval = ' '
		},
		.len = mx.col,
		.wid = mx.row,
		.x = 0,
		.y = 0
	};
	object_t obj1 = {
		.shape = RHOMBUS,
		.pixel = {
			.ulbd = BOLD,
			.bgnd = LBGPURPLE,
			.fgnd = LFGPURPLE,
			.cval = ' '
		},
		.len = mx.row - 3,
		.wid = mx.row - 3,
		.x = mx.col / 2 - 1,
		.y = 0
	};
	object_t *hdl0;
	object_t *hdl1;
	_stat = mx_fill(&mx, &((pixel_t){.ulbd = BOLD, .bgnd = LBGBLACK, .fgnd = LFGBLUE, .cval = '.'}));
	TEST_ASSERT_EQUAL(SUCCESS, _stat);

	_stat = mx_popup(&mx, &obj0, &hdl0);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	TEST_ASSERT_EQUAL(EMPTY, mx.lnobject[0].shape);
	TEST_ASSERT_EQUAL(EMPTY, mx.lnobject[1].shape);
	TEST_ASSERT_EQUAL(RECTANGLE, mx.lnobject[1].prev->shape);
	TEST_ASSERT_EQUAL(hdl0->shape, mx.lnobject[1].prev->shape);

	_stat = mx_popup(&mx, &obj1, &hdl1);
	TEST_ASSERT_EQUAL(SUCCESS, _stat);
	TEST_ASSERT_EQUAL(RHOMBUS, mx.lnobject[1].prev->shape);
	TEST_ASSERT_EQUAL(hdl1->shape, mx.lnobject[1].prev->shape);
	TEST_ASSERT_EQUAL(RHOMBUS, hdl0->next->shape);
	TEST_ASSERT_EQUAL_PTR(hdl1, hdl0->next);
	unsigned char key;
	while (1) {
		_stat = mx_render(&mx);
		TEST_ASSERT_EQUAL(SUCCESS, _stat);
		TEST_ASSERT_EQUAL(SUCCESS, mx_readkey(&key, 50));
		if (key == 'y') {
			hdl0->pixel.fgnd = HFGYELLOW;
			hdl0->pixel.bgnd = HBGYELLOW;
			hdl0->len--;
			hdl0->len--;
			hdl0->wid--;
			hdl0->wid--;
			hdl0->x++;
			hdl0->y++;
		} else if (key == 'Y') {
			hdl1->pixel.fgnd = HFGYELLOW;
			hdl1->pixel.bgnd = HBGYELLOW;
			hdl1->len--;
			hdl1->len--;
			hdl1->wid--;
			hdl1->wid--;
			hdl1->y++;
		} else if (key == 'b') {
			hdl0->pixel.fgnd = HFGBLUE;
			hdl0->pixel.bgnd = HBGBLUE;
			hdl0->len--;
			hdl0->len--;
			hdl0->wid--;
			hdl0->wid--;
			hdl0->x++;
			hdl0->y++;
		} else if (key == 'B') {
			hdl1->pixel.fgnd = HFGBLUE;
			hdl1->pixel.bgnd = HBGBLUE;
			hdl1->len--;
			hdl1->len--;
			hdl1->wid--;
			hdl1->wid--;
			hdl1->y++;
		} else if (key == 'c') {
			hdl0->pixel.fgnd = HFGCYAN;
			hdl0->pixel.bgnd = HBGCYAN;
			hdl0->len--;
			hdl0->len--;
			hdl0->wid--;
			hdl0->wid--;
			hdl0->x++;
			hdl0->y++;
		} else if (key == 'C') {
			hdl1->pixel.fgnd = HFGCYAN;
			hdl1->pixel.bgnd = HBGCYAN;
			hdl1->len--;
			hdl1->len--;
			hdl1->wid--;
			hdl1->wid--;
			hdl1->y++;
		} else if (key == 'q')
			return;
		mx_clear();
		mx_refresh(&mx);
	}
	return;
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_popup);
	return UNITY_END();
}
