.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=main shm_creat shm_read shm_write
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(BIN)

