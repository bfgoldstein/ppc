FLAGS=-O3

LIBS=-lm

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=pagerank

.PHONY : all clean debug run check_output

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC) problem_input problem_output

check_output: check_output.cpp
	$(CXX) $(FLAGS) -o check_output check_output.cpp

clean:
	$(RM) $(EXEC).o $(EXEC) check_output