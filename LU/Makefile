FLAGS=-O3

CC=icc

RM=rm -f

EXEC=LU

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
