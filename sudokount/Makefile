FLAGS=-O3 -std=c11 -march=native -Wall

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=sudokount

.PHONY : all clean debug run

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < sudokount1.in

clean:
	$(RM) $(EXEC).o $(EXEC)