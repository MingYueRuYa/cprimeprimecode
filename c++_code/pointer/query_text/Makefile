CC :=g++
CFLAG := -Wall -g -std=c++11
SOURCE := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SOURCE))
BIN := query_text
$(BIN): $(OBJ)
	$(CC) $(CFLAG) $^ -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFLAG) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJ) $(BIN)

