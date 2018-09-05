FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=matrix

.PHONY : all clean debug run

all: $(EXEC).cpp main.cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cpp -c -o main.o
	$(CXX) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

debug: $(EXEC).cpp main.cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cpp -c -o main.o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.o $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < matrix.in

clean:
	$(RM) $(EXEC).o $(EXEC)