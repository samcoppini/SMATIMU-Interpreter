CC=g++
CFLAGS= -Wall -Wextra -Werror -std=c++17 -pedantic -g

all:
	$(CC) $(CFLAGS) *.cpp -o "smt.exe"
