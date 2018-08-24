#include <iostream>
#include <fstream>

typedef uint uint;
const uint MAX_VALUE = 1<<20;

int main(int argc, char* argv[]) {
     uint n_seen = 0;
     uint value;
     uint count[MAX_VALUE];

     // Initializes the array
     for(uint i = 0; i < MAX_VALUE; ++i) {
          count[i] = 0;
     }

     // Reads the input file
     std::ifstream input(argv[1]);
     input >> value;
     while (!input.eof()) { 
          ++n_seen;
          ++count[value];  // Counts the ocurrence of a number
          input >> value;
     }
     input.close();

     // Open the output file
     std::ofstream output("problem_output");

     // Searching for the median
     uint half_seen = n_seen/2;
     // This algorithm assumes a odd numbered set. If it is even, then we
     // can "remove" the last element, making the set odd without altering
     // the results. This will be done subtracting 1 from the hals_seen.
     // Eventually we will restore the value removed and fix our median. 
     if (n_seen % 2 == 0) --half_seen;
     uint median = 0;
     uint seen_until_median = count[0];
     while (seen_until_median <= half_seen && median < MAX_VALUE) {
          ++median;
          seen_until_median = seen_until_median + count[median];
     };
     
     if (n_seen % 2) {
          output << median << std::endl;
     } else {
          double mean_median = median;
          ++median;
          while (count[median] == 0) ++median;
          mean_median = (mean_median+median)/2.0;
          output << mean_median << std::endl;
     }
     output.close();
     
}
