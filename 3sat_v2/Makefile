FLAGS=-O2

CC=gcc

RM=rm -f

EXEC=3sat

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) 3sat.c -c -o 3sat.o
	$(CC) $(FLAGS) 3sat.o -o $(EXEC) -lm

run:
	./$(EXEC)

clean:
	$(RM) 3sat.o $(EXEC)
