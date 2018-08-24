#include <iostream>
#include <stdio.h>

typedef unsigned int uint;

// Gets the input value from the input file
uint get_n(char* filename) {
     FILE* infile;
     infile = fopen(filename,"r");
     if (infile != NULL) {
          uint n;
          fscanf(infile,"%i", &n);
          fclose(infile);
          return n;
     } else {
          return 0;
     }
}

int main(int argc, char* argv[]){
     if (argc == 2) {
          uint n = get_n(argv[1]);
          if (n == 0) {
               std::cout << "Input error.\n";
               return 1;
          }
          // Open the output file
          FILE* outfile;
          outfile = fopen("problem_output","w");
          if (outfile == NULL) {
               std::cout << "Problem opening output file.\n";
               return 1;
          }
          // Initialize array
          uint* array = new uint[n+1];
          for (uint i = 2; i <= n; ++i) {
               array[i] = i;
          }
          // Start the sieve
          for (uint i = 2; i <= n; ++i) {
               if (array[i] != 0) {
                    // It's a prime. Print it!
                    fprintf(outfile,"%i \n",i);
                    uint k = i*i;
                    if (k <= n) {
                         for (uint j = k; j <= n; ++j) {
                              if (j % i == 0) array[j] = 0;
                         }
                    }
               }
          }
          fclose(outfile);
          delete[] array;
     } else {
          std::cout << "Usage: ./sieve problem_input" << std::endl;
     }
}
