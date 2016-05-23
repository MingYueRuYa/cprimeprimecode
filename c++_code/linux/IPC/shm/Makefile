BIN := shm_read shm_write
CC := gcc
CFALGS := -Wall -g
SOURCE := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SOURCE))
ALL:$(BIN)
%.o:%.c
	$(CC) $(CFALGS) $< -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFALGS) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJ) $(BIN)


