CC=g++
CFLAGS= -Wall -Wextra -Werror -std=c++17 -pedantic -O3 -Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:src/%.cpp=objs/%.o)

objs/%.o: src/%.cpp
	@mkdir -p objs
	@echo "Compiling $<..."
	@$(CC) $< -c -o $@ $(CFLAGS)

all: $(OBJS)
	@echo "Linking together executable..."
	@$(CC) $(CFLAGS) $(OBJS) -o "smt.exe"
	@echo "Finished compiling!"

clean:
	@echo "Removing object files..."
	@rm -rf objs
