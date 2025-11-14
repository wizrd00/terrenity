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

status_t init(matrix_t *mx, unsigned int vmin, unsigned int vtime);

status_t render(matrix_t *mx);

status_t refresh(matrix_t *mx);

status_t reset(matrix_t *mx);

status_t fill(matrix_t *mx, pixel_t *px);

status_t rotate(matrix_t *mx, rotate_t *rt);

#endif
