#include "terrenity.h"

struct termios default_stdin_tp;
struct termios default_stdout_tp;
struct termios stdin_tp;
struct termios stdout_tp;

static int set_stdin_attributes(void)
{
	stdin_tp.c_iflag &= ~(BRKINT | ICRNL);
	stdin_tp.c_iflag |= (IGNBRK | IGNPAR);
	stdin_tp.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | IEXTEN | ISIG);
	if (tcsetattr(fileno(stdin), TCSANOW, &stdin_tp) != 0)
		return -1;
	return 0;
}

static int set_stdout_attributes(void)
{
	stdout_tp.c_lflag &= ~(ICANON | IEXTEN | ISIG);
	if (tcsetattr(fileno(stdout), TCSANOW, &stdout_tp) != 0)
		return -1;
	return 0;
}

static status_t allocate_matrix(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	CHECK_NOTEQUAL(0, mx->row, BADSIZE);
	CHECK_NOTEQUAL(0, mx->col, BADSIZE);
	mx->floor_mx = (pixel_t **) calloc(sizeof(pixel_t *), mx->row);
	mx->float_mx = (pixel_t **) calloc(sizeof(pixel_t *), mx->row);
	CHECK_PTR(mx->floor_mx, ECALLOC);
	CHECK_PTR(mx->float_mx, ECALLOC);
	for (int i = 0; i < mx->row; i++) {
		mx->floor_mx[i] = (pixel_t *) calloc(sizeof(pixel_t), mx->col);
		mx->float_mx[i] = (pixel_t *) calloc(sizeof(pixel_t), mx->col);
		CHECK_PTR(mx->floor_mx[i], ECALLOC);
		CHECK_PTR(mx->float_mx[i], ECALLOC);
	}
	return _stat;
}

static void free_matrix(matrix_t *mx)
{
	for (int i = 0; i < mx->row; i++) {
		free(mx->floor_mx[i]);
		free(mx->float_mx[i]);
	}
	free(mx->floor_mx);
	free(mx->float_mx);
	return;
}

static status_t render_matrix(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	char buf[PIXEL_FORMAT_SIZE] = {0};
	uint8_t sec0 = 0, sec1 = 0, underline = 0, bold = 0;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++) {
			underline = mx->floor_mx[i][j].ulbd;
			bold = mx->floor_mx[i][j].ulbd;
			sec0 = (underline != 0) ? underline : bold;
			sec1 = (bold != 0) ? bold : underline;
			fprintf(stdout, PIXEL_FORMAT, sec0, sec1, mx->floor_mx[i][j].bgnd, mx->floor_mx[i][j].fgnd, mx->floor_mx[i][j].cval);
		}
	CHECK_NOTEQUAL(EOF, fflush(stdout), EFFLUSH);
	return _stat;
}

static status_t allocate_object(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	object_t *new_obj = (object_t *) malloc(sizeof(object_t));
	CHECK_PTR(new_obj, EMALLOC);
	new_obj->prev = mx->lnobject[1].prev;
	new_obj->next = mx->lnobject + 1;
	mx->lnobject[1].prev->next = new_obj;
	mx->lnobject[1].prev = new_obj;
	return _stat;
}

static void free_object(matrix_t *mx)
{
	object_t *obj = mx->lnobject[0].next;
	object_t *tmp_obj;
	while (obj != mx->lnobject + 1) {
		tmp_obj = obj->next;
		free(obj);
		obj = tmp_obj;
	}
	return;
}

static status_t render_object(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	object_t *obj = mx->lnobject[0].next;
	while (obj->shape != EMPTY) {
		CHECK_STAT(draw_shape(mx, obj));
		obj = obj->next;
	}
	return _stat;
}

status_t mx_init(matrix_t *mx, bool set_input, bool set_output)
{
	status_t _stat = SUCCESS;
	struct winsize ws;
	CHECK_NOTEQUAL(EOF, fputs(CLEAR, stdout), ERRWRIT);
	CHECK_EQUAL(0, tcgetattr(fileno(stdin), &default_stdin_tp), NOTCGET);	
	CHECK_EQUAL(0, tcgetattr(fileno(stdout), &default_stdout_tp), NOTCGET);
	if (set_input)
		CHECK_EQUAL(0, set_stdin_attributes(), NOTCSET);
	if (set_output)
		CHECK_EQUAL(0, set_stdout_attributes(), NOTCSET);
	CHECK_NOTEQUAL(-1, ioctl(fileno(stdout), TIOCGWINSZ, &ws), NOIOCTL);
	mx->row = ws.ws_row;
	mx->col = ws.ws_col;
	mx->update = YREQ;
	CHECK_STAT(allocate_matrix(mx));
	mx->lnobject[0].shape = EMPTY;
	mx->lnobject[1].shape = EMPTY;
	mx->lnobject[0].next = mx->lnobject + 1;
	mx->lnobject[1].prev = mx->lnobject;
	return _stat;
}

status_t mx_deinit(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	CHECK_STAT(mx_reset(mx));
	CHECK_STAT(mx_render(mx));
	free_matrix(mx);
	free_object(mx);
	CHECK_NOTEQUAL(-1, tcsetattr(fileno(stdin), TCSANOW, &default_stdin_tp), NOTCSET);
	CHECK_NOTEQUAL(-1, tcsetattr(fileno(stdout), TCSANOW, &default_stdout_tp), NOTCSET);
	return _stat;
}

status_t mx_refresh(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			mx->floor_mx[i][j] = mx->float_mx[i][j];
	mx->update = YREQ;
	return _stat;
}

status_t mx_render(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	if (mx->update == YREQ) {
		CHECK_STAT(render_object(mx));
		CHECK_STAT(mx_refresh(mx));
		CHECK_STAT(render_matrix(mx));
		mx->update = NREQ;
	}
	return _stat;
}

status_t mx_reset(matrix_t *mx)
{
	status_t _stat = SUCCESS;
	pixel_t nullpx = {.ulbd = 0, .bgnd = 0, .fgnd = 0, .cval = 0};
	object_t *obj = mx->lnobject[0].next;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			mx->float_mx[i][j] = nullpx;
	while (obj->shape != EMPTY) {
		obj->shape = EMPTY;
		obj = obj->next;
	}
	CHECK_STAT(mx_refresh(mx));
	return _stat;
}

status_t mx_fill(matrix_t *mx, pixel_t *px)
{
	status_t _stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			mx->float_mx[i][j] = *px;
	CHECK_STAT(mx_refresh(mx));
	return _stat;
}

status_t mx_popup(matrix_t *mx, object_t *obj, object_t **hdl)
{
	status_t _stat = SUCCESS;
	CHECK_NOTEQUAL(EMPTY, obj->shape, NOSHAPE);
	CHECK_EQUAL(0, allocate_object(mx), EMALLOC);
	*hdl = mx->lnobject[1].prev;
	(*hdl)->shape = obj->shape;
	(*hdl)->pixel = obj->pixel;
	(*hdl)->fill = obj->fill;
	(*hdl)->len = obj->len;
	(*hdl)->wid = obj->wid;
	(*hdl)->x = obj->x;
	(*hdl)->y = obj->y;
	mx->update = YREQ;
	return _stat;
}

status_t mx_popdown(matrix_t *mx, object_t *obj)
{
	status_t _stat = SUCCESS;
	obj->prev->next = obj->next->prev;
	free((void *) obj);
	mx->update = YREQ;
	return _stat;
}

status_t mx_rotate(matrix_t *mx, rotate_t rt)
{
	status_t _stat = SUCCESS;
	CHECK_EQUAL(mx->row, mx->col, ESQUARE);
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
	CHECK_STAT(mx_refresh(mx));
	return _stat;
}

status_t mx_readkey(unsigned char *key, unsigned char timeout)
{
	status_t _stat = SUCCESS;
	int tmp_val;
	stdin_tp.c_cc[VMIN] = (cc_t) 0;
	stdin_tp.c_cc[VTIME] = (cc_t) timeout;
	CHECK_EQUAL(0, tcsetattr(fileno(stdin), TCSANOW, &stdin_tp), NOTCSET);
	CHECK_EQUAL(0, fflush(stdin), EFFLUSH);
	tmp_val = getchar();
	CHECK_NOTEQUAL(EOF, tmp_val, ERRREAD);
	*key = (unsigned char) tmp_val;
	CHECK_EQUAL(0, fflush(stdin), EFFLUSH);
	return _stat;
}

status_t mx_readline(char *line, size_t size)
{
	status_t _stat = SUCCESS;
	CHECK_EQUAL(0, tcsetattr(fileno(stdin), TCSANOW, &default_stdin_tp), NOTCSET);
	CHECK_EQUAL(0, fflush(stdin), EFFLUSH);
	CHECK_PTR(fgets(line, size, stdin), FAILURE);
	CHECK_EQUAL(0, fflush(stdin), EFFLUSH);
	CHECK_EQUAL(0, tcsetattr(fileno(stdin), TCSANOW, &stdin_tp), NOTCSET);
	CHECK_EQUAL(0, fflush(stdin), EFFLUSH);
	return _stat;
}

status_t mx_clear(void)
{
	status_t _stat = SUCCESS;
	CHECK_NOTEQUAL(EOF, fputs(CLEAR, stdout), ERRWRIT);
	CHECK_EQUAL(0, fflush(stdout), EFFLUSH);
	return _stat;
}

status_t mx_echo_on(void)
{
	status_t _stat = SUCCESS;
	stdin_tp.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL);
	CHECK_EQUAL(0, tcsetattr(fileno(stdin), TCSANOW, &stdin_tp), NOTCSET);
	return _stat;
}

status_t mx_echo_off(void)
{
	status_t _stat = SUCCESS;
	stdin_tp.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	CHECK_EQUAL(0, tcsetattr(fileno(stdin), TCSANOW, &stdin_tp), NOTCSET);
	return _stat;
}
