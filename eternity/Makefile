FLAGS=-O3

RM=rm -f

EXEC=eternity

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
