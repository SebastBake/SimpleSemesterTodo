CC=gcc
CPPFLAGS=-Wall  -Werror

SRC=todo.c
TARGET=todo

all: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CPPFLAGS);

clean:
	rm -f src/*.o;

clear:
	clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear; clear;
