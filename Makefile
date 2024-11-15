CC = gcc
AR = ar

C_FLAGS = -Wall -O2 -o

all: build

build:
	$(CC) ucurses.c -c $(C_FLAGS) ucurses.o
	$(AR) -rsv libucurses.a ucurses.o

.PHONY: test
test:
	$(CC) ./test/test.c $(C_FLAGS) ./test.elf -L. -lucurses

.PHONY: test
clean:
	rm ucurses.o
	rm libucurses.a
	rm test.elf
