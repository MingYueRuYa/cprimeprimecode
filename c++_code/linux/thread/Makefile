BIN := threadbase thread_deliver  thread_pitfalls thread_attr thread_mutex thread_customer_product
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

thread_attr:thread_attr.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

thread_mutex:thread_mutex.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

thread_customer_product:thread_customer_product.o
	$(CC) $(CFALGS) $^ -o $@ -lpthread

.PHONY: clean
clean:
	-rm -rf $(OBJ) $(BIN)
