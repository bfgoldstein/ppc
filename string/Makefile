.PHONY = all clean test mpp

all : spec

clean :
	rm -rf spec *dSYM*

spec : spec.cc spec.hh
	g++ -std=c++11 -Wall -Wextra -O3 spec.cc -o spec

