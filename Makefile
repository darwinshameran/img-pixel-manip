.PHONY: all clean

CC := g++
CFLAGS := -std=c++14 -L/usr/lib/x86_64-linux-gnu -Wall -Wextra -pedantic -g
TARGET := project
LIBS := -lpng -lSDL2

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
%.o: %.cpp
	$(CC) $(CFLAGS) -lpng -lSDL2 -c $<
clean:
	rm -rf $(TARGET) *.o

