.PHONY: clean all
CC=gcc
CFLAGS=-Wall -g
BIN=sleep2 signal01 signal02 signal03 alarm signal_status signalaction aboutreliablesigstresstest
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)
