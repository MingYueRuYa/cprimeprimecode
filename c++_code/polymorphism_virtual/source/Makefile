CC=g++
CFLAG := -Wall -g -std=c++11
polymorphism:main.cpp
	$(CC) $(CFLAG) $^ -o $@.out

polymorphism_no_optimize:main.cpp
	$(CC) $(CFLAG) -fno-elide-constructors $^ -o $@.out

.PHONY: clean
clean:
	-rm -rf *.o *.out

