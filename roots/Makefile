
FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=roots_of_a_forest

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -o $(EXEC)$(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

run: $(EXEC)
	./$(EXEC) problem_input problem_output

clean:
	$(RM) $(EXEC).o $(EXEC)