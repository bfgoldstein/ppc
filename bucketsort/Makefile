FLAGS=-O2

CC=gcc

RM=rm -f

EXEC=bucketsort

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) main.c -c -o main.o
	$(CC) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
