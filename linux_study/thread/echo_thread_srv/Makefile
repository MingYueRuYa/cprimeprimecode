.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=echosrv echoclient
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

echosrv:echosrv.o
	$(CC) $(CFLAGS) $< -o $@ -lpthread

clean:
	rm -rf *.o $(BIN)
