class Puzzle {
     private:
          // Puzzle's size (lines x columns)
          int n;
          // Where data will be in fact stored
          int* store;
          int manhattan_distance(int row, int column);
          void right_pos(int value, int &x, int &y);
          void allocate(int size);
          // Position of the empty tile
          int hole_pos_x, hole_pos_y;
          // Possible moves
          bool move_up();
          bool move_down();
          bool move_left();
          bool move_right();
          // Calculates the solution's minimum cost
          void calc_cost();
          // For internal use
          void copy_puzzle(const Puzzle & p);
     public:
          int** puzzle;
          // Constructors
          Puzzle(int n);
          Puzzle(char* file);
          // Destructor
          ~Puzzle();
          bool move(int side);
          void print();
          // Write the number of moves in output_file
          void print_solution();
          // returns the total cost for the solution 
          // (moves made + moves still necessary)
          int total_cost() const;
          // Number of moves done since the starting positioning
          int moves_made;
          // Solution cost value
          int cost;
          bool operator<(const Puzzle &a) const;
          bool operator>(const Puzzle &a) const;
          Puzzle(const Puzzle & p);
          Puzzle& operator=(const Puzzle & p) throw();
};
