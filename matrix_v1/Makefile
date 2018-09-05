FLAGS=-O3

LIBS=-lm

DEBUGFLAGS = -g

CXX=g++

RM=rm -f

EXEC=sparse_matrix_multiplication

.PHONY : all clean debug run

all: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) main.cc $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).cc main.cc 
	$(CXX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(DEBUGFLAGS) main.cc $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC)
	./$(EXEC) < matrix_v1.in

clean:
	$(RM) $(EXEC).o $(EXEC)

