#ifndef TERRENITY_H
#define TERRENITY_H

#include "types.h"
#include "tool/rotation.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <asm/termbits.h>
#include <asm/termios.h>
#include <sys/ioctl.h>

#define PIXEL_FORMAT "\x1b[%d;%d;%d;%dm%c\x1b[0m"
#define PIXEL_FORMAT_SIZE 16 * sizeof (char)
#define ISZERO(val) (val.cval == '\0')
#define ISSQUARE(mx) (mx->row == mx->col)

status_t mx_init(matrix_t *mx, unsigned int vmin, unsigned int vtime);

status_t mx_render(matrix_t *mx);

status_t mx_refresh(matrix_t *mx);

status_t mx_reset(matrix_t *mx);

status_t mx_fill(matrix_t *mx, pixel_t *px);

status_t mx_rotate(matrix_t *mx, rotate_t rt);

status_t mx_readkey(unsigned char *key, unsigned int vmin, unsigned int vtime);

status_t mx_echo_on(void);

status_t mx_echo_off(void);

#endif
