FLAGS=-O3

CXX=g++

DEBUGFLAGS = -g

RM=rm -f

EXEC=selection

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
