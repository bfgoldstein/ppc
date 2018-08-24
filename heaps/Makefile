CC =icpc 
CPPFLAGS = -g #-m32

all: heap.cpp
	$(CC) $(CPPFLAGS) -o heap heap.cpp

run: heap problem_input
	./heap problem_input problem_output

clean:
	rm -rfv heap heap.dSYM problem_output
