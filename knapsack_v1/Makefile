FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=knapsack

.PHONY : all clean debug run

all: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cpp $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC) < knapsack_v1.in

clean:
	$(RM) $(EXEC)