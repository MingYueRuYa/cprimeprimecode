memory_manager:	memory_manager.cpp
	g++ memory_manager.cpp -Wall -g -o memory_manager

install:memory_manager
	./memory_manager

clean:
	rm -rf memory_manager
