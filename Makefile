CC = gcc

C_FLAGS = -Wall -O2 -o

all: build

build:
	$(CC) ucurses.c $(C_FLAGS) ucurses

clean:
	rm ucurses