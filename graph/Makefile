CC =icpc 
CPPFLAGS = -g #-m32

all: clustering_coefficient.cpp
	$(CC) $(CPPFLAGS) -o clustering_coefficient clustering_coefficient.cpp

run: clustering_coefficient problem_input
	./clustering_coefficient problem_input problem_output

clean:
	rm -rfv clustering_coefficient clustering_coefficient.dSYM problem_output
