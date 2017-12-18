.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=msgopen mqsend mqrecv mqnotify
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

msgopen:msgopen.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt

mqsend:mqsend.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt

mqrecv:mqrecv.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt

mqnotify:mqnotify.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt

clean:
	rm -rf *.o $(BIN)

