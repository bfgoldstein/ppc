FLAGS=-O3

CXX=g++

DEBUGFLAGS = -g

RM=rm -f

EXEC=pi

.PHONY : all clean debug run

all: $(EXEC).cpp main.cpp bigdecimal.cpp
	$(CXX) $(FLAGS) bigdecimal.cpp -c -o bigdecimal.o
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) bigdecimal.o $(EXEC).o main.cpp -o $(EXEC)

debug: $(EXEC).cpp main.cpp bigdecimal.cpp
	$(CXX) $(FLAGS) $(DEBUGFLAGS) bigdecimal.cpp -c -o bigdecimal.o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) bigdecimal.o $(EXEC).o main.cpp -o $(EXEC)

run:
	./$(EXEC) < pi_v1.in

clean:
	$(RM) $(EXEC).o bigdecimal.o $(EXEC)
