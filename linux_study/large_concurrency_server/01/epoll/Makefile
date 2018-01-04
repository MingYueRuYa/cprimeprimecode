.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=echopoll echocli
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o 

echopoll:echopoll.o
	$(CC) $(CFLAGS) $< -o $@

echocli:echocli.o
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(BIN)
