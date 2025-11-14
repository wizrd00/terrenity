#ifndef ROTATION_H
#define ROTATION_H

#include "types.h"

static inline int rotate_quarter_right(pixel_t **src_mx, pixel_t **dst_mx, size_t len) {
	size_t min = 0;
	size_t max = len - 1;
	while (min < max) {
		for (size_t i = min; i <= max; i++) {
			dst_mx[i][max] = src_mx[min][i];
			dst_mx[max][max + min - i] = src_mx[i][max];
			dst_mx[i][min] = src_mx[max][i];
		}
		min++;
		max--;
	}
}

#endif
