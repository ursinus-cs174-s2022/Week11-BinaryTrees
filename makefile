CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: tree

simplecanvas.o: simplecanvas/simplecanvas.h simplecanvas/simplecanvas.cpp
	$(CC) $(CFLAGS) -c simplecanvas/simplecanvas.cpp

tree: tree.cpp simplecanvas.o
	$(CC) $(CFLAGS) -o tree simplecanvas.o tree.cpp


clean:
	rm *.o tree