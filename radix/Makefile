FLAGS=-O2

CC=icpc

RM=rm -f

EXEC=radix

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) radix.cpp -c -o radix.o
	$(CC) $(FLAGS) radix.o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) radix.o $(EXEC)