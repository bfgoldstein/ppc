CC =icpc 
CPPFLAGS = -g #-m32

all: prefix-sum.cpp
	$(CC) $(CPPFLAGS) -o prefix-sum prefix-sum.cpp

run: prefix-sum problem_input
	./prefix-sum problem_input

clean:
	rm prefix-sum problem_output
