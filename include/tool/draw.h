#ifndef DRAW_H
#define DRAW_H

#include "types.h"
#include <stdio.h>

static inline status_t draw_shape_rectangle(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	size_t x = obj->x, y = obj->y, len = obj->len, wid = obj->wid;
	CHECK_EQUAL(RECTANGLE, obj->shape, BADSHAP);
	if ((x + len > mx->col) || (y + wid > mx->row))
		return _stat = BADSIZE;
	while ((len != 0) && (wid != 0)) {
		size_t xstep = len - 1;
		size_t ystep = wid - 1;
		for (size_t i = x; i <= x + xstep; i++) {
			mx->float_mx[y][i] = obj->pixel;
			mx->float_mx[y + ystep][i] = obj->pixel;
		}
		for (size_t i = y; i <= y + ystep; i++) {
			mx->float_mx[i][x] = obj->pixel;
			mx->float_mx[i][x + xstep] = obj->pixel;
		}
		if (!obj->fill)
			break;
		x++;
		y++;
		len -= (len > 1) ? 2 : 1;
		wid -= (wid > 1) ? 2 : 1;
	}
	return _stat;
}

static inline status_t draw_shape_rhombus(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	size_t x = obj->x, y = obj->y, len = obj->len, wid = obj->wid;
	CHECK_EQUAL(RHOMBUS, obj->shape, BADSHAP);
	if ((len != wid) || (x + 1 < len) || (x + len - 1 > mx->col) || (y + len + 3 > mx->row))
		return _stat = BADSIZE;
	while (true) {
		size_t head = y, tail = y + len + 1;
		size_t min = x, max = x;
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
		if (!obj->fill)
			break;
		y++;
		if (len == 0)
			break;
		if (len != 0)
			len -= (len > 1) ? 2 : 1;
	}
	return _stat;
}

static inline status_t draw_shape(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	if (!obj->active)
		return _stat;
	switch (obj->shape) {
		case EMPTY :
			break;
		case RECTANGLE :
			CHECK_STAT(draw_shape_rectangle(mx, obj));
			break;
		case RHOMBUS :
			CHECK_STAT(draw_shape_rhombus(mx, obj));
			break;
	}
	return _stat;
}

#endif
