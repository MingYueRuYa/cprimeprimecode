
CC=gcc
FLAG= -Wall -g

socketserver: socketserver.c
	$(CC) $(FLAG) -o $@ $^

socketmultiprocessserver: socketmultiprocessserver.c
	$(CC) $(FLAG) -o $@ $^

socketclient: socketclient.c
	$(CC) $(FLAG) -o $@ $^

experimentendian:experimentendian.c
	gcc -Wall -g $^ -o $@

basicsocketapi:basicsocketapi.c
	gcc -Wall -g $^ -o $@
	
clean:
	rm -rf socketserver socketclient basicsocketapi experimentendian
