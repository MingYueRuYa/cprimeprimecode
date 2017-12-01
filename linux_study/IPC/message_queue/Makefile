.PHONY: all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=message_queue
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rv *.o $(BIN)

