.PHONY: all clean

CC = g++
cflags = -lSDL2
input = sort.cpp

all: sort.out

sort.out: $(input)
	$(CC) $(cflags) $(input) -o sort.out

clean:
	rm -rf *.out
