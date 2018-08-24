CXX = icpc

CXXFLAGS = -strict-ansi

DEBUGFLAGS = -g

OPTFLAGS = -O3 -g0

LDFLAGS = -lm

EXEC = bbs

.PHONY : all clean

all : $(EXEC).cpp
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(EXEC).cpp -o $(EXEC)

debug : $(EXEC).cpp
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(EXEC).cpp -o $(EXEC)

clean :
	rm -rf *.o *.out $(EXEC)

