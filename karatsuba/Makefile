FLAGS=-O3

CXX=icpc

RM=rm -f

EXEC=karatsuba

all: $(EXEC)

$(EXEC):
	$(CXX) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
