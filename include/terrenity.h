#ifndef TERRENITY_H
#define TERRENITY_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <asm/termbits.h>
#include <asm/termios.h>
#include <sys/ioctl.h>

#define PIXEL_FORMAT "\x1b[%d;%d;%d;%dm%c\x1b[0m"
#define PIXEL_FORMAT_SIZE 16 * sizeof (char)
#define ISZERO(val) (val.cval == '\0')

status_t init(matrix_t *mx, unsigned int vmin, unsigned int vtime);

status_t refresh(matrix_t *mx);

#endif
