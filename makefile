CC=gcc
FLAGS=-ansi -pedantic
all:part1 part2

part1: 
	$(CC) -o part1 part1.c $(FLAGS)

part2: error.o
	$(CC) -o part2 part2.c error.o $(FLAGS)

error.o:
	$(CC) -c error.c $(FLAGS)

clean:
	-rm part1 part2
	-rm *.o
