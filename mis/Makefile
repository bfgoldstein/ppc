FLAGS=-O3 --std=c++11

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=mis

.PHONY : all clean debug run

all: $(EXEC).cc
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)