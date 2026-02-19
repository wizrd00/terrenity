# terrenity
lightweight, fast and simple terminal-based graphic rendering library.
This library provides several functions to manipulating terminal and drawing shapes on it.
It is very minimal and simple without high-level abstraction layer.

## Compile
I personaly use pcc to compile my project because it's written in pure C and also minimal.
But practical projects still must compile with gcc, so...

#### Compile with pcc
make sure you have installed pcc and make then run this command
``` bash
make CC=pcc
```

#### Compile with gcc
make sure you have installed gcc and make then run this command
``` bash
make CC=gcc
```

## Library Manual
To use terrenity in your project, first include terrenity.h header file.

This header consists declaration of these functions.
``` C
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
```

To use them we should be familiar with important types.

#### Important Types
First of all, each function returns ```status_t``` which is an ```enum``` to specify status of function.
On successful conditions, all functions must return SUCCESS; other values specify type of errors. 

Another important type is
``` C
typedef struct {
	uint8_t ulbd;
	uint8_t bgnd;
	uint8_t fgnd;
	uint8_t cval;
} pixel_t;
```

Each terminal pixel has 4 attributes
- ulbd : it can be macro BOLD or macro UNDERLINE
- bdnd : it specifies background color of pixel, colors are :
	- LBGBLACK : low intensity **black**
	- LBGRED : low intensity **red**
	- LBGGREEN : low intensity **green**
	- LBGYELLOW : low intensity **yellow**
	- LBGBLUE : low intensity **blue**
	- LBGPURPLE : low intensity **purple**
	- LBGCYAN : low intensity **cyan**
	- LBGWHITE : low intensity **white**
	- HBGBLACK : high intensity **black**
	- HBGRED : high intensity **red**
	- HBGGREEN : high intensity **green**
	- HBGYELLOW : high intensity **yellow**
	- HBGBLUE : high intensity **blue**
	- HBGPURPLE : high intensity **purple**
	- HBGCYAN : high intensity **cyan**
	- HBGWHITE : high intensity **white**
- fdnd : it specifies foreground color of pixel, colors are same as **bdnd** but with **FG** instead of **BG**
- cval : it specifies character of pixel


Most important type is
``` C
typedef struct {
	pixel_t **floor_mx;
	pixel_t **float_mx;
	object_t lnobject[2];
	update_t update;
	size_t row, col;
} matrix_t;
```

This ```struct``` includes two import matrixes called **floor_mx**, **float_mx**, also includes **lnobject** linked-list for shapes and **row**, **col** of terminal and a lock called **update**

- ```floor_mx``` : it's the main matrix; anything on terminal comes from it
- ```float_mx``` : this matrix is for changes; if in your program you wanna change something in terminal, you must change this matrix and apply changes to terminal with proper function of terrenity library
- ```lnobject``` : it's head and tail of our linked-list; you must not touch it!!!
- ```row``` : it's row of terminal
- ```col``` : it's column of terminal

#### Functions
##### function ```mx_init()```
Initiates and allocates matrixes, objects and terminal attributes

Prototype :
``` C
status_t mx_init(matrix_t *mx, bool set_input, bool set_output);
```

Arguments :
| argument name | description |
| --------------| ------------|
| ```mx``` | Main matrix structure, you **must** specify ```row``` and ```col```; you can use ```ioctl(fileno(stdout), TIOCGWINSZ, &ws)``` |
| ```set_input``` | If sets, the ```stdin``` will be convert to Raw Mode via ```cfmakeraw(stdin)``` |
| ```set_output``` | If sets, the ```stdout``` will be convert to Raw Mode via ```cfmakeraw(stdout)``` |

Return values :
- SUCCESS : successful
- BADSIZE : one of ```row``` or ```col``` is equal to zero (or both)
- NOTCGET : function ```tcgetattr()``` from termios.h failed, something is wrong about your terminal
- NOTCSET : can't set terminal attributes via ```tcsetattr()``` from termios.h
- ECALLOC : ```calloc()``` returned ```NULL```, probably out of memory

##### function ```mx_deinit()```
Deinitiates and frees matrixex, objects and resources and reverts terminal attributes in default

Prototype :
``` C
status_t mx_deinit(matrix_t *mx);
```

Arguments :
| argument name | description |
| --------------| ------------|
| ```mx``` | Main matrix |

Return values :
- SUCCESS : successful
- NOTCSET : can't set terminal attributes via ```tcsetattr()``` into default settings

##### function ```mx_refresh()```
This function copies the float matrix to the floor matrix

Arguments :
| argument name | description |
| --------------| ------------|
| ```mx``` | Main matrix |

Return values :
- SUCCESS : successful
