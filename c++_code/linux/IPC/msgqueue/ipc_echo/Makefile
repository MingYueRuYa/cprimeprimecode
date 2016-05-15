CC := gcc
CFLAGS := -Wall -g

BIN := echo_client echo_server
SOURCE := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SOURCE))
ALL: $(BIN)
%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJS): $(SOURCE)
	$(CC) $(CFLAGS) $^ -c

.PHONY:clean
clean:
	-rm -rf $(BIN) $(OBJS)
