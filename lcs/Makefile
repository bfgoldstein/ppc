FLAGS=-O3

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=lcs

.PHONY : all clean debug run

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) > output

clean:
	$(RM) $(EXEC).o $(EXEC)
