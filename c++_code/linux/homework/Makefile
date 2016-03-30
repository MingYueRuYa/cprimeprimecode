CC=gcc
FLAG= -Wall -g
signal:signal.c
	$(CC) $(FLAG) -o $@ $^

process:process.c
	$(CC) $(FLAG) -o $@ $^

reliablesig:reliablesig.c
	$(CC) $(FLAG) -o $@ $^

.PHONY: clean
clean:
	-rm *.o -rf	
