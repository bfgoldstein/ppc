FLAGS=-O3

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=life

.PHONY : all clean debug run

all: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cc $(EXEC).o -o $(EXEC)

debug: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < life_v1.in

clean:
	$(RM) $(EXEC).o $(EXEC)