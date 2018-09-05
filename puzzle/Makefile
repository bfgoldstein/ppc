FLAGS=-O3 -m32

LIBS=-lm

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=puzzle

.PHONY : all clean debug run

all: $(EXEC).cpp $(EXEC).h main.cpp 
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cpp $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).cpp $(EXEC).h main.cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cpp $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC) < puzzle.in

clean:
	$(RM) $(EXEC).o $(EXEC)