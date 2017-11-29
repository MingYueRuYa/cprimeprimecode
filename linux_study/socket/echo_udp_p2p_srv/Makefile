.PHONY:clean all

CC=g++
CFLAGS=-Wall -g
BIN= echosrv echoclient
all:$(BIN)
echosrv:echosrv.cpp
	${CC} ${CFLAGS}  $< -o $@

echoclient:echoclient.cpp
	${CC} ${CFLAGS}  $< -o $@

clean:
	rm -rf *.o $(BIN)
