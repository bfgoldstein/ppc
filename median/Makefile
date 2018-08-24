CC = icpc
CPPFLAGS = -g

all: median.cpp
	$(CC) $(CPPFLAGS) -o median median.cpp

run: median problem_input
	./median problem_input

clean:
	rm median problem_output
