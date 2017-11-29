.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=echosrv echoclient
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	g++ -Wall -g -c $< -o $@

echosrv:echosrv.cpp
	g++ -Wall -g  $< -o $@

clean:
	rm -rf *.o $(BIN)
