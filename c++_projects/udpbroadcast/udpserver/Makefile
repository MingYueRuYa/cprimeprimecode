BIN := udp_server
CC := g++
CFLAGS := -Wall -g -std=c++11
SOURCE := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SOURCE))
GLOG_LIB_PATH :=/usr/local/lib/libglog.a

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(GLOG_LIB_PATH) -lpthread -o $@

$(OBJ):$(SOURCE)
	$(CC) $(CFLAGS) $^ -c

.PHONY: clean
clean:
	rm -rf $(OBJ) $(BIN)
