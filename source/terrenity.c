#include "terrenity.h"

struct termios default_stdin_tp;
struct termios default_stdout_tp;
struct termios stdin_tp;
struct termios stdout_tp;

static void set_stdin_attributes(unsigned int vmin, unsigned int vtime) {
	stdin_tp.c_iflag &= ~(BRKINT | ICRNL);
	stdin_tp.c_iflag |= (IGNBRK | IGNPAR);
	stdin_tp.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | IEXTEN | ISIG);
	stdin_tp.c_cc[VMIN] = (cc_t) vmin;
	stdin_tp.c_cc[VTIME] = (cc_t) vtime;
	tcsetattr(stdin, TCSANOW, &stdin_tp);
	return;
}

static void set_stdout_attributes(void) {
	stdout_tp.c_lflag &= ~(ICANON | IEXTEN | ISIG);
	tcsetattr(stdout, TCSANOW, &stdout_tp);
	return;
}

static int allocate_matrix(matrix_t *mx) {
	if ((mx->row == 0) | (mx->col == 0))
		return -1;
	mx->floor_mx = (pixel_t **) calloc(sizeof (pixel_t *), mx->row);
	mx->float_mx = (pixel_t **) calloc(sizeof (pixel_t *), mx->row);
	if ((mx->floor_mx == NULL) | (mx->float_mx == NULL))
		return -1;
	for (int i = 0; i < mx->row; i++) {
		mx->floor_mx[i] = (pixel_t *) calloc(sizeof (pixel_t), mx->col);
		mx->float_mx[i] = (pixel_t *) calloc(sizeof (pixel_t), mx->col);
		if ((mx->floor_mx[i] == NULL) | (mx->float_mx[i] == NULL))
			return -1;
	}
	return 0;
}

status_t mx_init(matrix_t *mx, unsigned int vmin, unsigned int vtime) {
	status_t _stat = SUCCESS;
	struct winsize ws;
	tcgetattr(stdin, &default_stdin_tp);	
	tcgetattr(stdout, &default_stdout_tp);	
	set_stdin_attributes(vmin, vtime);
	set_stdout_attributes();
	CHECK_NOTEQUAL(-1, ioctl(stdout, TIOCGWINSZ, &ws), NOIOCTL);
	mx->row = ws.ws_row;
	mx->col = ws.ws_col;
	CHECK_NOTEQUAL(-1, allocate_matrix(mx), ECALLOC);
	return _stat;
}

status_t mx_render(matrix_t *mx) {
	status_t _stat = SUCCESS;
	char buf[PIXEL_FORMAT_SIZE] = {0};
	uint8_t sec0 = 0;
	uint8_t sec1 = 0;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++) {
			uint8_t underline = mx->ulbd >> 26;	
			uint8_t bold = mx->ulbd >> 24;	
			sec0 = (underline != 0) underline : bold;
			sec1 = (bold != 0) bold : underline;
			snprintf(buf, sizeof (buf), PIXEL_FORMAT, sec0, sec1, mx->bgnd, mx->fgnd, mx->cval);
			CHECK_EQUAL(sizeof (buf), fwrite(buf, sizeof (buf), stdout), EFWRITE);
		}
	CHECK_EQUAL(EOF, fflush(stdout), EFFLUSH);
	return _stat;
}

status_t mx_refresh(matrix_t *mx) {
	status_t _stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			if (!ISZERO(mx->float_mx[i][j]))
				mx->floor_mx[i][j] = mx->float_mx[i][j];
	return _stat;
}

status_t mx_reset(matrix_t *mx) {
	status_t _stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			mx->float_mx[i][j] = 0;
	refresh(mx);
	return _stat;
}

status_t mx_fill(matrix_t *mx, pixel_t *px) {
	status_t _stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			mx->float_mx[i][j] = *px;
	refresh(mx);
	return _stat;
}

status_t mx_rotate(matrix_t *mx, rotate_t rt) {
	status_t _stat = SUCCESS;
	CHECK_EQUAL(mx->row, mx->col, ESQUARE);
	refresh(mx);
	switch (rt) {
		case ROTCW :
			rotate_quarter_right(mx->floor_mx, mx->float_mx, mx->row);
			break;
		case ROTCC :
			rotate_quarter_left(mx->floor_mx, mx->float_mx, mx->row);
			break;
		default :
			return _stat = INVROTT;
	}
	refresh(mx);
	return _stat;
}
