CC:=g++
CFLAGS:=-Wall -g
SOURCE:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp, %.o, $(SOURCE))
BIN:=app origin_main
all: $(BIN)

app:main.o
	$(CC) $(CFLAGS) $^ -o $@

origin_main:origin_main.o
	$(CC) $(CFLAGS) $^ -o $@.out

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -rf *.out *.o app
