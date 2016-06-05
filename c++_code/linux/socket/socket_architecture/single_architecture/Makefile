
sockutil.o:sockutil.c
	gcc -Wall -g -c $^

sock_client:sock_client.o sockutil.o
	gcc -Wall -g $^ -o $@

sock_client.o:sock_client.c
	gcc -Wall -g -c $^

sock_server:sock_server.o sockutil.o
	gcc -Wall -g $^ -o $@

sock_server.o:sock_server.c
	gcc -Wall -g -c $^


.PHONY:clean
clean:
	-rm -rf *.o echoserver echoclient sock_server 

