
sockutil.o:sockutil.c
	gcc -Wall -g -c $^

sock_client:sock_client.o sockutil.o
	gcc -Wall -g $^ -o $@

sock_server:echoserver.o
	gcc -Wall -g $^ -o $@


