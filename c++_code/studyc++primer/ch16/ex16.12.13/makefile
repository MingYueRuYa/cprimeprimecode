EXE := obj

CC := g++
CFALGS := -Wall -g --std=c++11
# all cpp source files.
SOURCE := $(wildcard *.cpp)
TEMPLATE_FILES := $(wildcard *.h)
# substitute .cpp prefix to .o prefix
OBJS := $(patsubst %.cpp, %.o, $(SOURCE))

all:$(EXE)
$(EXE):$(OBJS)
	$(CC) $(CFALGS) $(TEMPLATE_FILES) $(OBJS) -o $(EXE)

$(OBJS):$(SOURCE)
	$(CC) $(CFALGS) $^ -c

.PHONY: clean
clean:
	-rm -rf $(EXE) $(OBJS) *.o

