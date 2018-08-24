CC = icpc
CPPFLAGS = -g #-m32

all: pagerank.cpp
	$(CC) $(CPPFLAGS) -o pagerank pagerank.cpp

run: pagerank problem_input
	./pagerank problem_input problem_output

check_output: check_output.cpp
	$(CC) $(CPPFLAGS) -o check_output check_output.cpp

clean:
	rm -rfv pagerank pagerank.dSYM problem_output check_output check_output.dSYM
