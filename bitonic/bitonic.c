/*********************************************************************
 *
 * https://www.cs.duke.edu/courses/fall08/cps196.1/Pthreads/bitonic.c
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LENGTH 8

FILE *fin, *fout;

char *strings;
long int N;

unsigned long int powersOfTwo[] =
{1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,
  65536,131072,262144,524288,1048576,2097152,4194304,8388608,
  16777216,33554432,67108864,134217728,268435456,536870912,
  1073741824};

#define ASCENDING  1
#define DESCENDING 0

void openfiles() {
  fin = fopen("sort.in", "r+");
  if (fin == NULL ) {
    perror("fopen fin");
    exit(EXIT_FAILURE);
  }

  fout = fopen("sort.out", "w");
  if (fout == NULL ) {
    perror("fopen fout");
    exit(EXIT_FAILURE);
  }
}

void closefiles(void) {
  fclose(fin);
  fclose(fout);
}

/** procedure compare()
 The parameter dir indicates the sorting direction, ASCENDING
 or DESCENDING; if (a[i] > a[j]) agrees with the direction,
 then a[i] and a[j] are interchanged.
 **/
void compare(int i, int j, int dir) {
  if (dir==(strcmp(strings+i*LENGTH,strings+j*LENGTH) > 0)) {
    char t[LENGTH];
    strcpy(t, strings+i*LENGTH);
    strcpy(strings+i*LENGTH, strings+j*LENGTH);
    strcpy(strings+j*LENGTH, t);
  }
}

/** Procedure bitonicMerge()
 It recursively sorts a bitonic sequence in ascending order,
 if dir = ASCENDING, and in descending order otherwise.
 The sequence to be sorted starts at index position lo,
 the parameter cbt is the number of elements to be sorted.
 **/
void bitonicMerge(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    int i;
    for (i=lo; i<lo+k; i++)
      compare(i, i+k, dir);
    bitonicMerge(lo, k, dir);
    bitonicMerge(lo+k, k, dir);
  }
}

/** function recBitonicSort()
 first produces a bitonic sequence by recursively sorting
 its two halves in opposite sorting orders, and then
 calls bitonicMerge to make them in the same order
 **/
void recBitonicSort(int lo, int cnt, int dir) {
  if (cnt>1) {
    int k=cnt/2;
    recBitonicSort(lo, k, ASCENDING);
    recBitonicSort(lo+k, k, DESCENDING);
    bitonicMerge(lo, cnt, dir);
  }
}

/** function sort()
 Caller of recBitonicSort for sorting the entire array of length N
 in ASCENDING order
 **/
void BitonicSort() {
  recBitonicSort(0, N, ASCENDING);
}

/** the main program **/ 
int main(int argc, char **argv) {

  long int i;

  openfiles();

  fscanf(fin, "%ld", &N);

  if(N > 1073741824 || powersOfTwo[(int)log2(N)] != N) {
    printf("%ld is not a valid number: power of 2 or less than 1073741824!\n", N);
    exit(EXIT_FAILURE);
  }

  strings = (char*) calloc(N, LENGTH);
  if (strings == NULL ) {
    perror("malloc strings");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < N; i++)
    fscanf(fin, "%s", strings + (i * LENGTH));

  BitonicSort();

  for (i = 0; i < N; i++)
    fprintf(fout, "%s\n", strings + (i * LENGTH));

  free(strings);
  closefiles();

  return EXIT_SUCCESS;
}

