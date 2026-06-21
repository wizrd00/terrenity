#ifndef ROTATION_H
#define ROTATION_H

#include "types.h"

static inline int rotate_quarter_right(pixel_t **src_mx, pixel_t **dst_mx, size_t len)
{
	size_t min = 0;
	size_t max = len - 1;
	while (min <= max) {
		for (size_t i = min; i <= max; i++) {
			dst_mx[i][max] = src_mx[min][i];
			dst_mx[max][i] = src_mx[max + min - i][max];
			dst_mx[i][min] = src_mx[max][i];
			dst_mx[min][i] = src_mx[max + min - i][min];
		}
		min++;
		max--;
	}
	return 0;
}

static inline int rotate_quarter_left(pixel_t **src_mx, pixel_t **dst_mx, size_t len)
{
	size_t min = 0;
	size_t max = len - 1;
	while (min <= max) {
		for (size_t i = min; i <= max; i++) {
			dst_mx[i][min] = src_mx[min][max + min - i];
			dst_mx[max][i] = src_mx[i][min];
			dst_mx[i][max] = src_mx[max][max + min - i];
			dst_mx[min][i] = src_mx[i][max];
		}
		min++;
		max--;
	}
	return 0;
}

#endif
