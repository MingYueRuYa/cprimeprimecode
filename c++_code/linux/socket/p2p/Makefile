CC=gcc
FLAG=-Wall -g

.PHONY: client server

client: client.c
	$(CC) $(FLAG) -o $@ $^

server: server.c
	$(CC) $(FLAG) -o $@ $^

clean:
	rm client server
