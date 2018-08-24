FLAGS=-O3 -lm

CC=pgcc

RM=rm -f

EXEC=tsp

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
