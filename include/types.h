#ifndef TYPES_H
#define TYPES_H

#include "escape_code.h"
#include "ansi_color.h"
#include <stddef.h>
#include <stdint.h>

typedef uint32_t cchar_t;

typedef struct {
	cchar_t floor_mx[][];
	cchar_t float_mx[][];
	size_t row, col;
} matrix_t;

#endif
