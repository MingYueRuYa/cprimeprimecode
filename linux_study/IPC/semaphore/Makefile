.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=semaphore_tool
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

