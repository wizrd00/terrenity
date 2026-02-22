#ifndef TYPES_H
#define TYPES_H

#include "escape_code.h"
#include "ansi_color.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define CHECK_STAT(val)\
	do {if (val != SUCCESS) {return _stat = val;}} while (0)

#define CHECK_PTR(val, err)\
	do {if (val == NULL) {return _stat = err;}} while (0)

#define CHECK_EQUAL(val0, val1, err)\
	do {if (val0 != val1) {return _stat = err;}} while (0)

#define CHECK_NOTEQUAL(val0, val1, err)\
	do {if (val0 == val1) {return _stat = err;}} while (0)

typedef unsigned char buffer_t;

typedef enum {
	SUCCESS,
	FAILURE,
	INVROTT,
	NOTCGET,
	NOTCSET,
	NOIOCTL,
	NOSHAPE,
	ERRREAD,
	ERRWRIT,
	ERRDRAW,
	ECALLOC,
	EMALLOC,
	EFFLUSH,
	ESQUARE,
	BADSIZE,
	BADSHAP
} status_t;

typedef enum {
	ROTCW,
	ROTCC
} rotate_t;

typedef enum {
	EMPTY,
	RECTANGLE,
	RHOMBUS
} shape_t;

typedef enum {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE
} color_t;

typedef enum {
	YREQ,
	NREQ
} update_t;

typedef struct {
	uint8_t ulbd;
	uint8_t bgnd;
	uint8_t fgnd;
	uint8_t cval;
} pixel_t;

typedef struct object {
	shape_t shape;
	pixel_t pixel;
	bool active;
	bool fill;
	size_t x, y;
	size_t len, wid;
	struct object *prev;
	struct object *next;
} object_t;

typedef struct {
	pixel_t **floor_mx;
	pixel_t **float_mx;
	buffer_t *buffer;
	object_t lnobject[2];
	update_t update;
	size_t row, col;
	size_t buffer_size;
} matrix_t;

#endif
