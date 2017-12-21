.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN= thread_demo1
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

thread_demo1:thread_demo1.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

clean:
	rm -rf *.o $(BIN)

