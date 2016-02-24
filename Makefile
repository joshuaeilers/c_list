CC = gcc
CFLAGS = -c -O2 -std=c99 -Wall -Wextra
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: test clean

bin/test: test.o $(OBJ)
	mkdir bin
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

test: bin/test
	./$<

clean:
	rm -rf bin *.o src/*.o
