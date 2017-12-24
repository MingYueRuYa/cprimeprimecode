.PHONY:all clean
CC=gcc
CFLAGS=-Wall -g -std=c99
BIN=thread_property thread_demo1 thread_tsd thread_product_customer	\
	thread_cond_pc
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

thread_property:thread_property.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

thread_demo1:thread_demo1.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

thread_tsd:thread_tsd.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

thread_product_customer:thread_product_customer.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

thread_cond_pc:thread_cond_pc.o
	$(CC) $(CFLAGS)  $< -o $@ -lpthread

clean:
	rm -rf *.o $(BIN)

