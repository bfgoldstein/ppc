#include <iostream>
#include <stdlib.h>
#include "puzzle.h"
#include <stdio.h>
#include <fstream>

Puzzle::Puzzle(int size) {
     allocate(size);
}

void Puzzle::allocate(int size) {
     n = size;
     // Allocate  storage
     store = (int*) new int[n*n];
     // Setup graph
     puzzle = (int**) new int[n];
     for (int row = 0; row < n; ++row) {
          puzzle[row] = &store[row * n];
	}
}

Puzzle::Puzzle(char* filename) {
     moves_made = 0;
     int val;
     FILE * file;
     file = fopen(filename,"r");
     if (file != NULL) {
          // The first value is the puzzle's size
          fscanf(file,"%i",&val);
          allocate(val);
          // Then we have each position's value
          for (int i = 0; i < n; ++i) {
               for (int j = 0; j < n; ++j) {
                    fscanf(file,"%i",&val);
                    puzzle[i][j] = val;
                    if (val == 0) {
                         hole_pos_x = i;
                         hole_pos_y = j;
                    }
               }
          }
          fclose(file);
          // Defite the puzzles's initial minimum solution cost
          calc_cost();
     } else {
          std::cout << "Error opening file.\n";
     }
}

Puzzle::~Puzzle() {
     if (puzzle) {
          delete[] puzzle;
     }
     if (store) {
          delete[] store;
     }
}

// Given a Value, it will set x and y with the 
// position that value should be
void Puzzle::right_pos(int value, int &x, int &y) {
     if (value == 0) {
          x = n - 1;
          y = n - 1;
          return;
     }
     if (value % n == 0) {
          x = (value/n) - 1;
          y = n-1;
     } else {
          x = value/n;
          y = (value % n) - 1;
     }
}

// Returns the manhattan distance between a value's current 
// position and it's correct position. The manhattan distance
// is given by the number of "hops" between two positions in
// a grid where only vertical and horizontal movements are
// allowed
int Puzzle::manhattan_distance(int x1, int y1) {
     int x2,y2;
     right_pos(puzzle[x1][y1],x2,y2);
     return (abs(x1-x2)+abs(y1-y2));
}

// Sets the "cost" to clear the puzzle. It is the sum of
// all manhattan distances of displaced values.
void Puzzle::calc_cost(){
     int count = 0, x_dest, y_dest; 
     for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
              if (puzzle[i][j] != 0) count += manhattan_distance(i,j);
          } 
     }
     cost = count;
}

// Moves a tile, effectively flipping it with the
// neighboring hole (the 0 tile). The possible sides
// of a move are 1 (up), 2 (down), 3 (left)  and 4 
// (right). It will return true if the move was 
// successful and false otherwhise.
// And remember that the movement uses the empty hole as the
// reference point.
bool Puzzle::move(int side) {
     bool result = false;
     switch (side) {
          case 1:
               result = move_up();
               break;
          case 2:
               result = move_down();
               break;
          case 3:
               result = move_left();
               break;
          case 4:
               result = move_right();
               break;
     }
     // Has it moved? If so, let's mark it.
     if (result) {
          ++moves_made;
          // And define it's new cost
          calc_cost();
     }
     return result;
}

bool Puzzle::move_up() {
     if (hole_pos_x > 0) {
          // Possible move
          puzzle[hole_pos_x][hole_pos_y] = 
               puzzle[hole_pos_x - 1][hole_pos_y];
          puzzle[hole_pos_x - 1][hole_pos_y] = 0;
          --hole_pos_x;
          return true;
     } else {
          // Impossible move
          return false;
     }
}


bool Puzzle::move_down() {
     if (hole_pos_x < n - 1) {
          // Possible move
          puzzle[hole_pos_x][hole_pos_y] = 
               puzzle[hole_pos_x + 1][hole_pos_y];
          puzzle[hole_pos_x + 1][hole_pos_y] = 0;
          ++hole_pos_x;
          return true;
     } else {
          // Impossible move
          return false;
     }
} 

bool Puzzle::move_left() {
     if (hole_pos_y > 0) {
          // Possible move
          puzzle[hole_pos_x][hole_pos_y] = 
               puzzle[hole_pos_x][hole_pos_y - 1];
          puzzle[hole_pos_x][hole_pos_y - 1] = 0;
          --hole_pos_y;
          return true;
     } else {
          // Impossible move
          return false;
     }
}

bool Puzzle::move_right() {
     if (hole_pos_y < n - 1) {
          // Possible move
          puzzle[hole_pos_x][hole_pos_y] = 
               puzzle[hole_pos_x][hole_pos_y + 1];
          puzzle[hole_pos_x][hole_pos_y + 1] = 0;
          ++hole_pos_y;
          return true;
     } else {
          // Impossible move
          return false;
     }
}

void Puzzle::print() {
     for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
               std::cout << puzzle[i][j] << "   ";
          }
          std::cout << std::endl;
     }
}

int Puzzle::total_cost() const {
     return (moves_made + cost);
}

// Overloaded < operator
bool Puzzle::operator<(const Puzzle &a) const {
     return total_cost() < a.total_cost();
}

// Overloaded > operator
bool Puzzle::operator>(const Puzzle &a) const {
     return total_cost() > a.total_cost();
}

// Copy constructor
Puzzle::Puzzle(const Puzzle & p) {
     allocate(p.n);
     copy_puzzle(p);
}

// Overloaded assignment operator
Puzzle& Puzzle::operator=(const Puzzle & p) throw() {
     copy_puzzle(p);  
     return *this;
}

// Copies the data and state of another puzzle
void Puzzle::copy_puzzle(const Puzzle & p) {
     std::memcpy(store,p.store,n*n*sizeof(int));
     cost = p.cost;
     moves_made = p.moves_made;
     hole_pos_x = p.hole_pos_x;
     hole_pos_y = p.hole_pos_y;
}

// Prints the solution in output_file
void Puzzle::print_solution() {
     std::ofstream output("problem_output");
     output << moves_made << std::endl;
     output.close();
}
