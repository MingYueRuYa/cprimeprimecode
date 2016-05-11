BIN= udp_client udp_server
ALL:$(BIN)
%.o:%.c
	gcc -Wall -g $< -o $@

.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf udp_client udp_server
