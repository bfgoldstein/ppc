FLAGS=-O3

DEBUGFLAGS = -g

CXX=gcc

RM=rm -f

EXEC=black-scholes

.PHONY : all clean debug run

all: $(EXEC).cpp $(EXEC).h
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cpp $(EXEC).h
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
