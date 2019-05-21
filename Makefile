CFLAGS = -ansi -Werror -Wall -pedantic -g
CC = gcc
OBJ = linked_list.o adventure.o main.o fileIO.o
EXEC = main

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c adventure.h fileIO.h
	$(CC) main.c -c $(CFLAGS)

linked_list.o : linked_list.c adventure.h linked_list.h
	$(CC) linked_list.c -c $(CFLAGS)

adventure.o : adventure.c adventure.h linked_list.h
	$(CC) adventure.c -c $(CFLAGS)

fileIO.o : fileIO.h fileIO.c
	$(CC) fileIO.c -c $(CFLAGS)

clean : 
	rm -f $(EXEC) $(OBJ)
