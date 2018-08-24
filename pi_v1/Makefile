FLAGS=-O2

CC=icpc

RM=rm -f

EXEC=pi

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) bigdecimal.cpp -c -o bigdecimal.o
	$(CC) $(FLAGS) pi.cpp -c -o pi.o
	$(CC) $(FLAGS) bigdecimal.o pi.o main.cpp -o $(EXEC)

run:
	./$(EXEC) < input

clean:
	$(RM) pi.o bigdecimal.o $(EXEC)
