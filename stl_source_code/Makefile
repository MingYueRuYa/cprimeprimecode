CC:=g++
CFLAGS:=-Wall -g
SOURCE:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCE))
BIN:=app
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BIN)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -rf *.o app
