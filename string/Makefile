FLAGS=-O3 -std=c++11 -Wall -Wextra

DEBUGFLAGS = -g

CXX=g++

CC=gcc

RM=rm -f

EXEC=spec

.PHONY : all clean debug run

all: $(EXEC).cc $(EXEC).hh
	$(CXX) $(FLAGS) $(EXEC).cc -o $(EXEC)

debug: $(EXEC).cc $(EXEC).hh
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < spec.in

clean:
	$(RM) $(EXEC).o $(EXEC)

