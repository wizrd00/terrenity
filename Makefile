VERSION := 0.9.0
CC = pcc
ifeq ($(CC), pcc)
CFLAGS := -std=c99 -g -O3 -Wc,-Werror=implicit-function-declaration,-Werror=missing-prototypes,-Werror=pointer-sign,-Werror=sign-compare,-Werror=strict-prototypes,-Werror=shadow
CFLAGS_PIC := -shared -fPIC
else ifeq ($(CC), gcc)
CFLAGS := -std=c99 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wcast-align -Wconversion -Wsign-conversion -Wshadow -Wswitch-enum
CFLAGS_PIC := -shared -fPIC
else
$(error unsupported compiler : $(CC))
endif

SRC_DIR := source
INC_DIR := include
BIN_DIR := binary
LIB_DIR := library

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
HDR_FILES := $(wildcard $(INC_DIR)/*.h) $(wildcard $(INC_DIR)/tool/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

LIB_FLAGS := -Wl,--library-path=$(LIB_DIR),-rpath=$(LIB_DIR)

INCLUDE_FLAGS := -I$(INC_DIR)

LIBTERRENITY := $(LIB_DIR)/libterrenity.so

POINTER_SYM := "\e[91m->\e[0m"

$(LIBTERRENITY) : $(OBJ_FILES) $(HDR_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[96mlinking modules into" $@ "\e[0m"
	$(CC) $(CFLAGS) $(CFLAGS_PIC) -o $@ $(OBJ_FILES)
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mstrip" $@ "\e[0m"
	@strip $@

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@/usr/bin/echo -e $(POINTER_SYM) "\e[93mcompiling module" $< "\e[0m"
	$(CC) -c $(CFLAGS) $(CFLAGS_PIC) $(INCLUDE_FLAGS) -o $@ $<

clean :
	rm $(wildcard $(BIN_DIR)/*.o) $(wildcard $(LIBTERRENITY))

clear : clean
