CC = icpc
CPPFLAGS = -g #-m32

all: sieve.cpp
	$(CC) $(CPPFLAGS) -o sieve sieve.cpp

run: sieve problem_input
	./sieve problem_input

clean:
	rm sieve problem_output
