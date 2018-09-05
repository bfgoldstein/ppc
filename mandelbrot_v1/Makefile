FLAGS=-O3

LIBS=-lm

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=mandelbrot

.PHONY : all clean debug run

all: $(EXEC).cpp main.cpp 
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cpp $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).cpp main.cpp 
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cpp $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC) < mandelbrot_v1.in

clean:
	$(RM) $(EXEC).o $(EXEC)

