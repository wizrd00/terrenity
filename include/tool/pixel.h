#ifndef PIXEL_H
#define PIXEL_H

#include "types.h"
#include <stdio.h>

#define PIXEL "\x1b[%d;%d;%d;%dm%c"
#define PIXEL_SIZE 16

static inline void pixelcpy(buffer_t *restrict buf, pixel_t *restrict pix)
{
	int underline = (int) pix->ulbd & 0x04, bold = (int) pix->ulbd & 0x01;
	buf[0] = '\x1b';
	buf[1] = '[';
	buf[2] = (underline) ? underline : bold + '0';
	buf[3] = ';';
	buf[4] = (bold) ? bold : underline + '0';
	buf[5] = ';';
	buf[6] = (pix->bgnd / 100) + '0';
	buf[7] = ((pix->bgnd / 10) % 10) + '0';
	buf[8] = (pix->bgnd % 10) + '0';
	buf[9] = ';';
	buf[10] = (pix->fgnd / 100) + '0';
	buf[11] = ((pix->fgnd / 10) % 10) + '0';
	buf[12] = (pix->fgnd % 10) + '0';
	buf[13] = 'm';
	buf[14] = pix->cval;
	buf[15] = '\0';
	return;
}

#endif
