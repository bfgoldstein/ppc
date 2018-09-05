FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=clique

.PHONY : all clean debug run

all: $(EXEC).cc main.cc clique.hh
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc main.cc clique.hh
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.o $(EXEC).o -o $(EXEC)

run: $(EXEC) clique.in
	./$(EXEC) < clique.in

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
