FLAGS=-O3 

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=shellsort

IN_EXEC=shellsort-generator

.PHONY : all clean debug run generator clean_generator

all: $(EXEC).c $(EXEC).h main.c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) main.c $(EXEC).o -o $(EXEC)

debug: $(EXEC).c $(EXEC).h main.c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) main.c $(EXEC).o -o $(EXEC)

run: $(EXEC) shellsort.in
	./$(EXEC) < shellsort.in

clean:
	$(RM) *.o $(EXEC)

generator: $(IN_EXEC).c
	$(CC) $(FLAGS) $(IN_EXEC).c -c -o $(IN_EXEC).o
	$(CC) $(FLAGS) $(IN_EXEC).o -o $(IN_EXEC)

clean_generator:
	$(RM) $(IN_EXEC).o $(IN_EXEC) shellsort.in