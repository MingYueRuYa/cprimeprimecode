memory_manager:	memory_manager.cpp
	g++ memory_manager.cpp -Wall -g -o memory_manager

install:memory_manager
	./memory_manager

test:	test.cpp
	g++ $^ -Wall -g -o $@.out

clean:
	rm -rf memory_manager
