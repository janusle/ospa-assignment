CC=gcc
FLAGS=-ansi -pedantic
all:progOne launcher

progOne: 
	$(CC) -o progOne progOne.c $(FLAGS)

launcher: error.o utility.o
	$(CC) -o launcher launcher.c error.o utility.o $(FLAGS)

utility.o:
	$(CC) -c utility.c $(FLAGS) 

error.o:
	$(CC) -c error.c $(FLAGS)

clean:
	-rm progOne launcher
	-rm *.o
	-rm result
