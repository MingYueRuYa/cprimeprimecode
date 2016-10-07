BIN := basethread
CC := g++
CFALGS := -Wall -g -std=c++11
SOURCE := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SOURCE))
ALL:$(OBJ)
	$(CC) $(CFALGS) $(OBJ) -o $(BIN)

$(OBJ):$(SOURCE)
	$(CC) $(CFALGS) $^ -c

.PHONY:clean
clean:
	-rm -rf $(OBJ) $(BIN)


