#ifndef TERRENITY_H
#define TERRENITY_H

#include "types.h"
#include "tool/rotation.h"
#include "tool/draw.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#define PIXEL_FORMAT "\x1b[%d;%d;%d;%dm%c\x1b[0m"
#define PIXEL_FORMAT_SIZE 16 * sizeof(char)
#define ISSQUARE(mx) (mx->row == mx->col)

status_t mx_init(matrix_t *mx, bool set_input, bool set_output);

status_t mx_deinit(matrix_t *mx);

status_t mx_refresh(matrix_t *mx);

status_t mx_render(matrix_t *mx);

status_t mx_reset(matrix_t *mx);

status_t mx_fill(matrix_t *mx, pixel_t *px);

status_t mx_popup(matrix_t *mx, object_t *obj, object_t **hdl);

status_t mx_popdown(matrix_t *mx, object_t *obj);

status_t mx_rotate(matrix_t *mx, rotate_t rt);

status_t mx_unlock(matrix_t *mx);

status_t mx_readkey(unsigned char *key, unsigned char timeout);

status_t mx_clear(void);

status_t mx_echo_on(void);

status_t mx_echo_off(void);

#endif
