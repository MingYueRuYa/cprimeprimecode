.PHONY: clean all
CC=gcc
CFLAGS= -Wall -g
BIN=fork fork_fd vfork hello abortprogram demo_deamon fork_wait
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf *.o $(BIN)


fork:fork.c
	gcc -Wall -g -o $@  $^

fork_fd:fork_fd.c
	gcc -Wall -g -o $@  $^

vfork:vfork.c
	gcc -Wall -g -o $@  $^

clean:
	sudo rm -rf fork
	sudo rm -rf fork_fd
	sudo rm -rf vfork 
