
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
	
test_socket_backlog_client:test_socket_backlog_client.c gcc -Wall -g $^ -o $@

test_socket_backlog_server:test_socket_backlog_server.c
	gcc -Wall -g $^ -o $@
	
single_select_multi_server:single_select_multi_server.c
	gcc -Wall -g $^ -o $@

.PHNOY: clean
clean:
	-rm -rf socketserver socketclient basicsocketapi experimentendian test_socket_backlog_client test_socket_backlog_server single_select_multi_server 
