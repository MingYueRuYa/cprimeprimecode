.PHONY:ALL
CC=g++
CFLAG=-std=c++11  -Wall -g
SOURCE=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SOURCE))
ALL: singleton

singleton:$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFLAG) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJ) singleton


