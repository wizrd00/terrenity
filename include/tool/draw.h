#ifndef DRAW_H
#define DRAW_H

#include "types.h"
#include <stdio.h>

static inline status_t draw_shape_rectangle(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	CHECK_EQUAL(RECTANGLE, obj->shape, BADSHAP);
	if ((obj->x + obj->len > mx->col) || (obj->y + obj->wid > mx->row))
		return _stat = BADSIZE;
	size_t xstep = obj->len - 1;
	size_t ystep = obj->wid - 1;
	for (size_t i = obj->x; i <= obj->x + xstep; i++) {
		mx->float_mx[obj->y][i] = obj->pixel;
		mx->float_mx[obj->y + ystep][i] = obj->pixel;
	}
	for (size_t i = obj->y; i <= obj->y + ystep; i++) {
		mx->float_mx[i][obj->x] = obj->pixel;
		mx->float_mx[i][obj->x + xstep] = obj->pixel;
	}
	return _stat;
}

static inline status_t draw_shape_rhombus(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	CHECK_EQUAL(RHOMBUS, obj->shape, BADSHAP);
	if ((obj->len != obj->wid) || (obj->x + 1 < obj->len) || (obj->x + obj->len - 1 > mx->col) || (obj->y + obj->len + 3 > mx->row))
		return _stat = BADSIZE;
	size_t head = obj->y, tail = obj->y + obj->len + 2;
	size_t min = obj->x, max = obj->x;
	while (head <= tail) {
		mx->float_mx[head][min] = obj->pixel;
		mx->float_mx[head][max] = obj->pixel;
		mx->float_mx[tail][min] = obj->pixel;
		mx->float_mx[tail][max] = obj->pixel;
		head++;
		tail--;
		max++;
		min--;
	}
	return _stat;
}

static inline status_t draw_shape_triangle(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	return _stat;
}

static inline status_t draw_shape(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	switch (obj->shape) {
		case RECTANGLE :
			CHECK_STAT(draw_shape_rectangle(mx, obj));
			break;
		case RHOMBUS :
			CHECK_STAT(draw_shape_rhombus(mx, obj));
			break;
		case TRIANGLE :
			CHECK_STAT(draw_shape_triangle(mx, obj));
			break;
	}
	return _stat;
}

#endif
