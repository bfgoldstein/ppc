FLAGS=-O3

CC=icpc

RM=rm -f

EXEC=selection

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
