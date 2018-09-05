FLAGS=-O3 -std=c++11 -Wall

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=shortest_superstring

IN_EXEC=shortest_superstring-generator

.PHONY : all clean debug run generator clean_generator

all: $(EXEC).cc
	$(CXX) $(FLAGS) $(EXEC).cc -o $(EXEC)

debug: $(EXEC).cc
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < shortest_superstring.in

clean:
	$(RM) $(EXEC).o $(EXEC)

generator: $(IN_EXEC).cc
	$(CXX) $(FLAGS) $(IN_EXEC).cc -o $(IN_EXEC)

clean_generator:
	$(RM) $(IN_EXEC).o $(IN_EXEC) shortest_superstring.in
