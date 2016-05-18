BIN := pipe
CC := gcc
CFLAGS := -Wall -g
SOURCR := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SOURCR))

ALL: $(BIN)
%.o:%.c
	$(CC) $(CFLAGS)  $< -o $@

$(OBJS):$(SOURCR)
	$(CC) $(CFLAGS) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJS) $(BIN)
