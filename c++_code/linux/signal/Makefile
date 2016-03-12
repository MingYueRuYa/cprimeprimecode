.PHONY: clean all
CC=gcc
CFLAGS=-Wall -g
BIN=sleep2 signal01 signal02 signal03
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)
