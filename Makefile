CC=g++
CFLAGS=-I.
MF=main.cpp

main: main.cpp table.h
	$(CC) -o main.o main.cpp $(CFLAGS)