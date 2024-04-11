.PHONY: all clean

CC = g++
cflags = -Wall -O2 -lSDL2
input = sort.cpp

all: sort

sort: $(input)
	$(CC) $(cflags) $(input) -o sort

clean:
	rm -rf sort
