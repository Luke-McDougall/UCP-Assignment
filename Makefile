CFLAGS = -ansi -Werror -Wall -pedantic -g
CC = gcc
OBJ = linked_list.o adventure.o TreasureHunter.o fileIO.o
EXEC = TreasureHunter

ifdef TreasureHunter
CFLAGS += -D TreasureHunter=1
endif
ifdef TreasureHunterAI
CFLAGS += -D TreasureHunterAI=1
endif
ifdef TreasureHunterLog
CFLAGS += -D TreasureHunterLog=1
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

TreasureHunter.o : TreasureHunter.c adventure.h fileIO.h TreasureHunter.h
	$(CC) TreasureHunter.c -c $(CFLAGS)

linked_list.o : linked_list.c adventure.h linked_list.h
	$(CC) linked_list.c -c $(CFLAGS)

adventure.o : adventure.c adventure.h linked_list.h
	$(CC) adventure.c -c $(CFLAGS)

fileIO.o : fileIO.h fileIO.c
	$(CC) fileIO.c -c $(CFLAGS)

 
clean : 
	rm -f $(EXEC) $(OBJ)
