CC=g++
CFLAGS=-Wall

all: main

main: Tp2.o pagetable.o memory.o
	$(CC) -o main Tp2.o pagetable.o memory.o

Tp2.o: Tp2.cpp auxiliaries.hpp fifo.hpp lru.hpp pagetable.hpp memory.hpp
	$(CC) -o Tp2.o Tp2.cpp -c

pagetable.o: pagetable.cpp pagetable.hpp
	$(CC) -o pagetable.o pagetable.cpp -c $(CFLAGS)

memory.o: memory.cpp memory.hpp
	$(CC) -o memory.o memory.cpp -c $(CFLAGS) 