.PHONY:clean all

CC=gcc
CFLAGS= -Wall -g
BIN= third_io four_file_dir
SOURCE=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o, $(SOURCE))
all:$(BIN)

third_io:third_io.c
	$(CC) $(CFLAGS) $^ -o $@.out

four_file_dir:four_file_dir.c
	$(CC) $(CFLAGS) $^ -o $@.out

clean:
	rm -rf *.out *.o
