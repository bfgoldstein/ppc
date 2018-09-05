FLAGS=-O3

CC=gcc

RM=rm -f

EXEC=gauss

IN_EXEC=gauss_v1-generator

.PHONY : all clean debug run generator clean_generator

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < gauss.in

clean:
	$(RM) $(EXEC).o $(EXEC)

generator: $(IN_EXEC).c
	$(CC) $(FLAGS) $(IN_EXEC).c -c -o $(IN_EXEC).o
	$(CC) $(FLAGS) $(IN_EXEC).o -o $(IN_EXEC)

clean_generator:
	$(RM) $(IN_EXEC).o $(IN_EXEC) gauss.in