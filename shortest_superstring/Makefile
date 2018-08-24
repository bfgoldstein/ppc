.PHONY = all clean bin

all : bin

bin : shsup

clean:
	rm -rf shsup

shsup: shortest_superstring.cc
	$(CXX) -std=c++11 -Wall -O3 shortest_superstring.cc -o shsup

