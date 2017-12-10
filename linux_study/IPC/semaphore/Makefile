.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=semaphore_tool semaphore_demo dining_philosopher
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

