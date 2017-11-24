.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=echosrv echoclient
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)
