.PHONY: all clean
CC=gcc
CFLAGS=-Wall -g
BIN=echo_sockpair
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(BIN)

