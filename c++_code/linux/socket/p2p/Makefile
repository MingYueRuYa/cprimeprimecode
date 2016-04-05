.PHONY: clean ALL

CC=gcc
FLAG=-Wall -g
BIN=client server

ALL:$(BIN)
%.o:%.c
	$(CC) $(FLAG) -c $< -o $@

#client: client.c
#	$(CC) $(FLAG) -o $@ $^
#
#server: server.c
#	$(CC) $(FLAG) -o $@ $^

clean:
	rm -rf *.o $(BIN)
