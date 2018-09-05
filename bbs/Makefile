CXX = gcc

CXXFLAGS = -strict-ansi

DEBUGFLAGS = -g

OPTFLAGS = -O3 -g0

LDFLAGS = -lm

RM=rm -f

EXEC = bbs

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(EXEC).cpp -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < input > output

clean:
	$(RM) *.o *.out $(EXEC)

