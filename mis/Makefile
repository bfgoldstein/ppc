FLAGS=-O3 --std=c++11

CC=g++

RM=rm -f

EXEC=mis

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
