CC=g++
BIN := main
CFLAGS :=-Wall -g -std=c++11
SOURCR = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SOURCR))

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ):$(SOURCR)
	$(CC) $(CFLAGS) $^ -c 

.PHONY:clean
clean:
	-rm -rf $(OBJ) $(BIN)


