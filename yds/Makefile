FLAGS=-O3 --c++11

CC=pgCC

RM=rm -f

EXEC=yds

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
