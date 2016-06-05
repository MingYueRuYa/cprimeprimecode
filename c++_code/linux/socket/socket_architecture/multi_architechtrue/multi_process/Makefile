
#sockutil.o:sockutil.c
#	gcc -Wall -g -c $^
#
#sock_client:sock_client.o sockutil.o
#	gcc -Wall -g $^ -o $@
#
#sock_client.o:sock_client.c
#	gcc -Wall -g -c $^
#
#sock_server:sock_server.o sockutil.o
#	gcc -Wall -g $^ -o $@
#
#sock_server.o:sock_server.c
#	gcc -Wall -g -c $^

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

#$(OBJ):$(SOURCE)
#	$(CC) $(CFLAGS) $^ -c
#

.PHONY:clean
clean:
	-rm -rf *.o echoserver echoclient sock_server sock_client

