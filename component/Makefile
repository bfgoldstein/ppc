FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=component_labeling

.PHONY : all clean debug run

all: $(EXEC).cc main.cc component_labeling.hh
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) main.o $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc main.cc component_labeling.hh
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc- c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc -c -o main.o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.o $(EXEC).o -o $(EXEC)

run: $(EXEC) component.in
	./$(EXEC) < component.in

clean:
	$(RM) main.o $(EXEC).o $(EXEC)
