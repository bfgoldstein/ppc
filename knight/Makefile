FLAGS=-O3

DEBUGFLAGS = -g

CCX=gcc

RM=rm -f

EXEC=knight

.PHONY : all clean debug run

all: $(EXEC).cpp
	$(CCX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CCX) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).cpp
	$(CCX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CCX) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC)
	./$(EXEC) < input > output

clean:
	$(RM) $(EXEC).o $(EXEC)