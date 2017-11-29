.PHONY:clean all

CC=gcc
CFLAGS=-Wall -g
BIN= echosrc echoclient
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)
