.PHONY: all clean

all: g++ -lSDL2 sort.cpp -o sort.out

clean: rm -rf *.out
