#ifndef DRAW_H
#define DRAW_H

#include "types.h"

static inline status_t draw_shape_rectangle(matrix_t *mx, object_t *obj) {
	status_t _stat = SUCCESS;
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

static inline status_t draw_shape_rhombus(matrix_t *mx, object_t *obj) {}

static inline status_t draw_shape_triangle(matrix_t *mx, object_t *obj) {}

#endif
