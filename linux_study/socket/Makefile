SUBDIRS= echo_pipe_srv echosrv echo_n_srv echo_readline_srv echo_select_srv \
		 echo_timeout_select_srv echo_poll_srv
.PHONY:clean all $(SUBDIRS)
CC=gcc
CFLAGS=-Wall -g
BIN=01byteorder 02addr getiplist
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

# all clean:
# 	$(MAKE) $(SUBDIRS) TARGET=$@

clean:
	rm -rf *.o $(BIN)
	$(MAKE) $(SUBDIRS) TARGET=$@

$(SUBDIRS):
	$(MAKE) -C $@ $(TARGET)
