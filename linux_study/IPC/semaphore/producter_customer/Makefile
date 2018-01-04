.PHONY: clean all

CC=gcc
CFLAG=-Wall -g
BIN=shmfifo_recv shmfifo_send shmfifo_free
OBJ1=shmfifo_send.o shmfifo.o ipc.o
OBJ2=shmfifo_recv.o shmfifo.o ipc.o
OBJ3=shmfifo_free.o shmfifo.o ipc.o
all: $(BIN)
%.o:%.c
	$(CC) $(CFLAG) -c $<

shmfifo_send:$(OBJ1)
	$(CC) $(CFLAG) $^ -o $@

shmfifo_recv:$(OBJ2)
	$(CC) $(CFLAG) $^ -o $@

shmfifo_free:$(OBJ3)
	$(CC) $(CFLAG)  $^ -o $@

clean:
	rm *.o $(BIN)
