FLAGS=-O3

LIBS=-lm

DEBUGFLAGS = -g

CC=gcc

RM=rm -f

EXEC=tsp

all: $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC) $(LIBS)

debug: $(EXEC).c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(EXEC).o -o $(EXEC) $(LIBS)

run: $(EXEC) tsp_v2.in
	./$(EXEC) < tsp_v2.in

clean:
	$(RM) $(EXEC).o $(EXEC)
