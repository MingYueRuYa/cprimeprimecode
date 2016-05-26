BIN := threadbase thread_deliver  thread_pitfalls
CC := gcc
CFALGS := -Wall -g
SOURCE := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SOURCE))
ALL:$(BIN)
%.o:%.c
	$(CC) $(CFALGS) $< -c -o $@

threadbase:threadbase.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

thread_deliver:thread_deliver.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

thread_pitfalls:thread_pitfalls.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

.PHONY: clean
clean:
	-rm -rf $(OBJ) $(BIN)
