#ifndef TERRENITY_H
#define TERRENITY_H

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <asm/termbits.h>
#include <asm/termios.h>
#include <sys/ioctl.h>

status_t init(matrix_t *mx, unsigned int vmin, unsigned int vtime);

status_t refresh(matrix_t *mx);

#endif
