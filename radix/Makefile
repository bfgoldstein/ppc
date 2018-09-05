FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

CC=gcc

RM=rm -f

EXEC=radix

IN_EXEC=radix-generate

.PHONY : all clean debug run generator clean_generator

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < radix.in

clean:
	$(RM) $(EXEC).o $(EXEC)

generator: $(IN_EXEC).c
	$(CC) $(FLAGS) $(IN_EXEC).c -c -o $(IN_EXEC).o
	$(CC) $(FLAGS) $(IN_EXEC).o -o $(IN_EXEC)

clean_generator:
	$(RM) $(IN_EXEC).o $(IN_EXEC) radix.in