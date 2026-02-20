CC := pcc

BUILD_DIR := build
INCLUDE_DIR := ../../include
LIB_DIR := ../../library
UNITY_DIR := ../libunity

ifeq ($(CC), pcc)
	CFLAGS := -std=c99 -g -O3 -Wc,-Werror=implicit-function-declaration,-Werror=missing-prototypes,-Werror=pointer-sign,-Werror=sign-compare,-Werror=strict-prototypes,-Werror=shadow -pthread
	CFLAGS_PIC := -shared -fPIC
	LIB_FLAGS := -Wl,--library-path=../../library,--library=unity,--library=terrenity,-rpath=../../library

else ifeq ($(CC), gcc)
	CFLAGS := -std=c99 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wcast-align -Wconversion -Wsign-conversion -Wshadow -Wswitch-enum -pthread
	CFLAGS_PIC := -shared -fPIC
	LIB_FLAGS := -L$(LIB_DIR) -lunity -Wl,-rpath=$(LIB_DIR)
else
	$(error unsupported compiler : $(CC))
endif

TEST_SRC := test.c
TEST_OBJ := $(BUILD_DIR)/test.o

TYPES_HDR := ../../include/types.h

test.elf : $(TEST_OBJ) $(TYPES_HDR)
	@echo linking object files $<
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $@ $<

$(TEST_OBJ) : $(TEST_SRC) $(TYPES_HDR)
	@echo compiling $^
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -I$(UNITY_DIR) -o $@ $<

memcheck : test.elf
	@echo start checking test.elf for any memory bug
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$^

clean :
	rm -rf build/* test.elf
