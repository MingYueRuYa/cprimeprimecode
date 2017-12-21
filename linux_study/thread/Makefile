.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=thread_property
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

thread_property:thread_property.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

clean:
	rm -rf *.o $(BIN)

