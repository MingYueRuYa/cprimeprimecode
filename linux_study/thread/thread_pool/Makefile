.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g
BIN=threadpool
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

threadpool:main.o condition.o thread_pool.o
	$(CC) $(CFLAGS)  $^ -o $@ -lpthread -lrt


clean:
	rm -rf *.o $(BIN)

