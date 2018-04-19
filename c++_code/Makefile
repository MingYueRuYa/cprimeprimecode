CC=g++
CFLAG := -Wall -g
inheritclass:inheritclass.cpp
	$(CC) $(CFLAG) $^ -o $@.out

typeid:typeid.cpp
	$(CC) $(CFLAG) $^ -o $@.out

virtual_class_deep_unstanderd:virtual_class_deep_unstanderd.cpp
	$(CC) $(CFLAG) $^ -o $@.out

rvalue:rvalue.cpp
	$(CC) $(CFLAG) -std=c++11 $^ -o $@.out

.PHONY: clean
clean:
	-rm -rf *.o *.out

