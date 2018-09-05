FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=sum

.PHONY : all clean debug run

all: $(EXEC).cc
	$(CXX) $(FLAGS) $(EXEC).cc -o $(EXEC)

debug: $(EXEC).cc
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < sum_v1.in

clean:
	$(RM) $(EXEC).o $(EXEC)