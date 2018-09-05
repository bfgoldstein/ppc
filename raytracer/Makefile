FLAGS=-O3

CXX=g++

RM=rm -f

EXEC=raytracer

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < raytracer.in

clean:
	$(RM) $(EXEC).o $(EXEC)