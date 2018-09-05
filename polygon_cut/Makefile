FLAGS=-O2 -lm

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=polygon_cut

.PHONY : all clean debug run

all: $(EXEC)
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
