FLAGS=-O3

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=eternity

.PHONY : all clean debug run

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC) eternity.in
	./$(EXEC) < eternity.in

clean:
	$(RM) $(EXEC).o $(EXEC)
