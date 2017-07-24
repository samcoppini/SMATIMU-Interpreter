CC=g++
CFLAGS= -Wall -Wextra -Werror -std=c++17 -pedantic -O3
SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:%.cpp=%.o)

%.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o "smt.exe"

clean:
	rm *.o
