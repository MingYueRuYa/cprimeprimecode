BIN := udp_server
CC := g++
CFLAGS := -Wall -g
SOURCE := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SOURCE))
$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFLAGS) $^ -c

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN)
