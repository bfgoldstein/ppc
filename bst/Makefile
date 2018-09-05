FLAGS=-O3

DEBUGFLAGS = -g

CXX=gcc

RM=rm -f

EXEC=obst

.PHONY : all clean debug run

all: $(EXEC).cc main.cc obst.hh
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc main.cc obst.hh
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.o $(EXEC).o -o $(EXEC)

run: $(EXEC) bst.in
	./$(EXEC) < bst.in

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
