.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=shmopen shmwrite shmread
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

shmopen:shmopen.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt
 
shmwrite:shmwrite.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt
 
shmread:shmread.o
	$(CC) $(CFLAGS)  $< -o $@ -lrt
 
# mqnotify:mqnotify.o
# 	$(CC) $(CFLAGS)  $< -o $@ -lrt
# 
# mqunlink:mqunlink.o
# 	$(CC) $(CFLAGS)  $< -o $@ -lrt

clean:
	rm -rf *.o $(BIN)

