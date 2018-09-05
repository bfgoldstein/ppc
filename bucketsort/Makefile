FLAGS=-O3

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=bucketsort

.PHONY : all clean debug run

all: $(EXEC).c main.c bucketsort.h
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) main.c -c -o main.o
	$(CC) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

debug: $(EXEC).c main.c bucketsort.h
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) main.c -c -o main.o
	$(CC) $(FLAGS) $(DEBUGFLAGS) main.o $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
