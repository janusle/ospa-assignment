CC=gcc
FLAGS=-ansi -pedantic
all:part1

part1: 
	$(CC) -o part1 part1.c 

clean:
	-rm part1
