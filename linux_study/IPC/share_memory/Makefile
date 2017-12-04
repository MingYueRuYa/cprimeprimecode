.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=main
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

