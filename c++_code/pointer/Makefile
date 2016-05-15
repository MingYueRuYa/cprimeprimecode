smart_pointer:smart_pointer.cpp
	g++ -Wall -g $< -o $@

strblob.o:strblob.cpp
	g++ -std=c++11 -Wall -g $< -c 

pointer:strblob.o main.cpp
	g++ -std=c++11 -Wall -g strblob.o main.cpp -o $@

.PHONY:clean
clean:
	-rm -rf smart_pointer 
