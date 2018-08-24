FLAGS=-O2

CC=icc

RM=rm -f

EXEC=dna

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) dna.c -c -o dna.o
	$(CC) $(FLAGS) dna.o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) dna.o $(EXEC)