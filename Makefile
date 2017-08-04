CC=g++
CFLAGS= -Wall -Wextra -Werror -std=c++17 -pedantic -O3 -Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:src/%.cpp=objs/%.o)

objs/%.o: src/%.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o "smt.exe"

clean:
	rm $(OBJS)
