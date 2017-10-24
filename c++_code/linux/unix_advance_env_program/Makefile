.PHONY:clean

CC=gcc
CFLAGS= -Wall -g

third_io:third_io.c
	$(CC) $(CFLAGS) $^ -o $@.out

clean:
	rm -rf *.out *.o
