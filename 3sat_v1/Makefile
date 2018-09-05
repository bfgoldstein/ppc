FLAGS=-O3 

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=3sat

.PHONY : all clean debug run

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC)

run: $(EXEC) 3sat_v1.in
	./$(EXEC) < 3sat_v1.in

clean:
	$(RM) *.o $(EXEC)
