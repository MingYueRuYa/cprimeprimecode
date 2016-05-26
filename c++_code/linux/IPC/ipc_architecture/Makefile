BIN := main
CC := gcc
CFALGS := -Wall -g
SOURCE := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SOURCE))
$(BIN):$(OBJ)
	$(CC) $(CFALGS) $(OBJ) -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFALGS) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJ) $(BIN)


