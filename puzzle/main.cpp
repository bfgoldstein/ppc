#include <iostream>
#include <stdio.h>
#include "puzzle.h"
#include <queue>
#include <vector>

typedef std::priority_queue<Puzzle, std::vector<Puzzle>, std::greater<Puzzle> > PuzzleQueue;

int main(int argc, char* argv[]) {
     char blah;
     int count = 0;
     if (argc == 2) {
          // Loads puzzle
          Puzzle p(argv[1]);
          // Initialize Priority queue
          PuzzleQueue pq;
          pq.push(p);
          do {
               // Gets the most promising partial solution
               p = pq.top();
               pq.pop();
               ++count;
               if (p.cost == 0) {
                    // It is our solution!
                    p.print_solution();
                    return 0;
               } else {
                    // Tests for each possible movement and 
                    // adds it to the queue
                    for (int i = 1; i <= 4; ++i) {
                         Puzzle p2 = p;
                         if (p2.move(i)) {
                              pq.push(p2);
                         }
                    }
               }
          } while (true);
     } else {
          std::cout << "Usage: ./bbound input_file\n";
     }
}
