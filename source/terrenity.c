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
	mx->floor_mx = (cchar_t *) calloc(sizeof (cchar_t), sizeof (mx->row));
	mx->float_mx = (cchar_t *) calloc(sizeof (cchar_t), sizeof (mx->row));
	if ((mx->floor_mx == NULL) | (mx->float_mx == NULL))
		return -1;
	for (int i = 0; i < mx->row; i++) {
		mx->floor_mx[i] = (cchar_t *) calloc(sizeof (cchar_t), sizeof (mx->col));
		mx->float_mx[i] = (cchar_t *) calloc(sizeof (cchar_t), sizeof (mx->col));
		if ((mx->floor_mx[i] == NULL) | (mx->float_mx[i] == NULL))
			return -1;
	}
	return 0;
}

status_t init(matrix_t *mx, unsigned int vmin, unsigned int vtime) {
	status_t stat = SUCCESS;
	struct winsize ws;
	tcgetattr(stdin, &default_stdin_tp);	
	tcgetattr(stdout, &default_stdout_tp);	
	set_stdin_attributes(vmin, vtime);
	set_stdout_attributes();
	if (ioctl(stdout, TIOCGWINSZ, &ws) == -1)
		return stat = NOIOCTL;
	mx->row = ws.ws_row;
	mx->col = ws.ws_col;
	if (allocate_matrix(mx) == -1)
		return stat = ECALLOC;
	return stat;
}

status_t render(matrix_t *mx) {
	status_t stat = SUCCESS;
	unsigned char underline = 0;
	unsigned char bold = 0;
	unsigned char background = 0;
	unsigned char foreground = 0;
	unsigned char character = '\0';
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++) {
			underline = (mx->floor_mx[i][j] >> 0x18) & 0x4;
			bold = (mx->floor_mx[i][j] >> 0x18) & 0x1;		
			background = (mx->floor_mx[i][j] >> 0x10) & 0xff; 
			foreground = (mx->floor_mx[i][j] >> 0x8) & 0xff;
			character = ((mx->floor_mx[i][j] & 0xff) < 32) ? ' ' : (mx->floor_mx[i][j] >> 0x0) & 0xff;
			printf(PRINT_FORMAT, underline, bold, background, foreground, character);
		}
	return stat;
}

status_t refresh(matrix_t *mx) {
	status_t stat = SUCCESS;
	for (int i = 0; i < mx->row; i++)
		for (int j = 0; j < mx->col; j++)
			if (mx->float_mx[i][j] != 0)
				mx->floor_mx[i][j] = mx->float_mx[i][j];
	return stat;
}
