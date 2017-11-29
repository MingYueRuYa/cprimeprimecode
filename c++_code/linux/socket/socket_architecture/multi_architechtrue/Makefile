.PHONY: ALL
CC=gcc
CFLAGS=-Wall -g 
SOURCE=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SOURCE))

ALL: sockutil.o client server

client:
	$(CC) $(CFLAGS) multi_process_sock_client.c sockutil.o -o $@
	
server:
	$(CC) $(CFLAGS) sock_server.c sockutil.o -o $@

sockutil.o:sockutil.c
	$(CC) $(CFLAGS) $^ -c

.PHONY:clean
clean:
	-rm -rf *.o server client sockutil.o

