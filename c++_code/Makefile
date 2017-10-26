CC=g++
CFLAG := -Wall -g
inheritclass:inheritclass.cpp
	$(CC) $(CFLAG) $^ -o $@.out

typeid:typeid.cpp
	$(CC) $(CFLAG) $^ -o $@.out

.PHONY: clean
clean:
	-rm -rf *.o *.out

