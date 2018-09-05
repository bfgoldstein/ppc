FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=sieve

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < sieve.in

clean:
	$(RM) $(EXEC).o $(EXEC)
