stl: stl.cpp
	g++ -Wall -g stl.cpp -std=c++11 -o $@.out
	
uninitializer_function: uninitializer_function.cpp
	g++ -Wall -g $< -std=c++11 -o $@.out

.PHONY:clean
clean:
	rm -rf *.out *.o
