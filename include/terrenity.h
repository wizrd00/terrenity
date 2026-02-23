#ifndef TERRENITY_H
#define TERRENITY_H

#include "types.h"
#include "tool/pixel.h"
#include "tool/draw.h"
#include "tool/rotation.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#define ISSQUARE(mx) (mx->row == mx->col)
#define OFFSET(i, j, k) (((i * k) + j) * PIXEL_SIZE)

status_t mx_init(matrix_t *restrict mx, bool set_input, bool set_output);

status_t mx_deinit(matrix_t *restrict mx);

status_t mx_refresh(matrix_t *restrict mx);

status_t mx_render(matrix_t *restrict mx);

status_t mx_reset(matrix_t *restrict mx);

status_t mx_setpixel(matrix_t *restrict mx, pixel_t *restrict px, size_t x, size_t y);

status_t mx_fill(matrix_t *restrict mx, pixel_t *restrict px);

status_t mx_popup(matrix_t *restrict mx, object_t *restrict obj, object_t **restrict hdl);

status_t mx_popdown(matrix_t *restrict mx, object_t *restrict obj);

status_t mx_rotate(matrix_t *restrict mx, rotate_t rt);

status_t mx_unlock(matrix_t *restrict mx);

status_t mx_readkey(unsigned char *key, unsigned char timeout);

status_t mx_clear(void);

status_t mx_echo_on(void);

status_t mx_echo_off(void);

status_t mx_hide_cursor(void);

status_t mx_show_cursor(void);

#endif
