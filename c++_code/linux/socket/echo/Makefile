.PHONY: all clean
CC=gcc
CFLAGS=-Wall -g
BIN=echoclient echoserver
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm %.o $(BIN)
