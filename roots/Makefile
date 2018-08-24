CC =icpc 
CPPFLAGS = -g #-m32

all: roots_of_a_forest.cpp
	$(CC) $(CPPFLAGS) -o roots_of_a_forest roots_of_a_forest.cpp

run: roots_of_a_forest problem_input
	./roots_of_a_forest problem_input problem_output

clean:
	rm -rfv roots_of_a_forest roots_of_a_forest.dSYM problem_output
