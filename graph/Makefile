FLAGS=-O3

DEBUGFLAGS = -g

CXX=gcc

RM=rm -f

EXEC=clustering_coefficient

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) problem_input problem_output

clean:
	$(RM) $(EXEC).o $(EXEC)
