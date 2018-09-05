FLAGS=-std=c++11 -O3 -Wall

DEBUGFLAGS = -g

CXX=gcc

RM=rm -f

EXEC=huffman

.PHONY : all clean debug run

all: $(EXEC).cc
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < huffman.in

clean:
	$(RM) $(EXEC).o $(EXEC)
