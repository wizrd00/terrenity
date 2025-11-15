#include "terrenity.h"

struct termios default_stdin_tp;
struct termios default_stdout_tp;
struct termios stdin_tp;
struct termios stdout_tp;
object_t link_objects[2];

static int set_stdin_attributes(void) {
	stdin_tp.c_iflag &= ~(BRKINT | ICRNL);
	stdin_tp.c_iflag |= (IGNBRK | IGNPAR);
	stdin_tp.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | IEXTEN | ISIG);
	if (tcsetattr(stdin, TCSANOW, &stdin_tp) != 0)
		return -1;
	return 0;
}

static int set_stdout_attributes(void) {
	stdout_tp.c_lflag &= ~(ICANON | IEXTEN | ISIG);
	if (tcsetattr(stdout, TCSANOW, &stdout_tp) != 0)
		return -1;
	return 0;
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

static int allocate_object(void) {
	object_t *new_obj = (object_t *) malloc(sizeof (object_t));
	new_obj->prev = link_object[1].prev;
	new_obj->next = link_object + 1;
	link_object[1].prev->next = new_obj;
	link_object[1].prev = new_obj;
	return 0;
}

status_t mx_init(matrix_t *mx) {
	status_t _stat = SUCCESS;
	struct winsize ws;
	CHECH_EQUAL(0, tcgetattr(stdin, &default_stdin_tp), NOTCGET);	
	CHECK_EQUAL(0, tcgetattr(stdout, &default_stdout_tp), NOTCGET);
	CHECK_EQUAL(0, set_stdin_attributes(), NOTCSET);
	CHECK_EQUAL(0, set_stdout_attributes(), NOTCSET);
	CHECK_NOTEQUAL(-1, ioctl(stdout, TIOCGWINSZ, &ws), NOIOCTL);
	mx->row = ws.ws_row;
	mx->col = ws.ws_col;
	CHECK_NOTEQUAL(-1, allocate_matrix(mx), ECALLOC);
	link_object[0].shape = EMPTY;
	link_object[1].shape = EMPTY;
	link_object[0].next = link_object + 1;
	link_object[1].prev = link_object;
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

status_t mx_popup(matrix_t *mx, object_t *obj) {
	status_t _stat = SUCCESS;
	switch (shape) {
		case RECTANGLE :
			CHECK_EQUAL(0, draw_shape_rectangle(mx->float_mx, obj), ERRDRAW);
			break;
		case CIRCLE :
			CHECK_EQUAL(0, draw_shape_circle(mx->float_mx, obj), ERRDRAW);
			break;
		default :
			return _stat = NOSHAPE;
	}
	refresh(mx);
	CHECK_EQUAL(0, allocate_object(), EMALLOC)
	memcpy(link_object[1].prev, obj, sizeof (object_t));
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

status_t mx_readkey(unsigned char *key, unsigned int vmin, unsigned int vtime) {
	status_t _stat = SUCCESS;
	int tmp_val = getchar();
	stdin_tp.c_cc[VMIN] = (cc_t) vmin;
	stdin_tp.c_cc[VTIME] = (cc_t) vtime;
	CHECK_EQUAL(0, tcsetattr(stdin, TSCANOW, &stdin_tp), NOTCSET);
	CHECK_NOTEQUAL(EOF, tmp_val, ERRREAD);
	*key = (unsigned char) tmp_val;
	return _stat;
}

status_t mx_echo_on(void) {
	status_t _stat = SUCCESS;
	stdin_tp.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL);
	CHECK_EQUAL(0, tcsetattr(stdin, TCSANOW, &stdin_tp), NOTCSET);
	return _stat;
}

status_t mx_echo_off(void) {
	status_t _stat = SUCCESS;
	stdin_tp.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	CHECK_EQUAL(0, tcsetattr(stdin, TCSANOW, &stdin_tp), NOTCSET);
	return _stat;
}
