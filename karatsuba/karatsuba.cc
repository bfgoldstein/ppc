// fast Karatsuba multiplication
// 21 Jan 1999, Carl Burch, cburch@cmu.edu
//
// This program implements a reasonably efficient multiplication
// algorithm (Karatsuba multiplication) and times it against the
// traditional grade-school technique.
//
// (c) 1999, Carl Burch
// This may not be copied without retaining this copyright notice,
// and it may not be distributed in modified form.
#include <stdlib.h>
#include <stdio.h>

#define MAX_DIGITS 2097152
// Numbers will be stored as an array arr of integers.
// arr[0] is a one's digit, arr[1] the 10's digit, etc.
// Note that this means that how we normally write numbers and how
// we normally draw arrays is reversed, which is a bit confusing.
//
// Before changing this constant, note the warning mentioned below
// about potential overflow problems.

#define KARAT_CUTOFF 4
// When karatsuba() gets to numbers with at most KARAT_CUTOFF
// digits, it reverts to straight grade-school multiplication.
// (This helps because karatsuba() is slower than grade-school
// multiplication for tiny values of n.)

// Within karatsuba() and gradeSchool(), we do not worry about whether
// the `digits' are actually between 0 and 9; this is fixed after we
// return from the call with doCarry().
//
// WARNING! This is potentially problematic if the `digits' get so
// large that we have overflow. With 32-bit ints and KARAT_CUTOFF==4,
// we are safe up to 1024 digits; more than this is potentially
// problematic. One easy way to avoid this is to call doCarry()
// for larger values, but the below code does not do this.

void            karatsuba(int *a, int *b, int *ret, int d);
void            gradeSchool(int *a, int *b, int *ret, int d);
void            doCarry(int *a, int d);
void            getNum(int *a, int *d_a);
void            printNum(int *a, int d);

int             a[MAX_DIGITS]; // first multiplicand
int             b[MAX_DIGITS]; // second multiplicand
int             r[6 * MAX_DIGITS]; // result goes here

int
main() {
  int             d_a; // length of a
  int             d_b; // length of b
  int             d; // maximum length
  int             i; // counter

  getNum(a, &d_a);
  getNum(b, &d_b);

  if(d_a < 0 || d_b < 0) {
    printf("0\n");
    exit(0);
    return 0;
  }

  // let d be the smallest power of 2 greater than d_a and d_b,
  // and zero out the rest of a and b.
  i = (d_a > d_b) ? d_a : d_b;
  for(d = 1; d < i; d *= 2);
  for(i = d_a; i < d; i++) a[i] = 0;
  for(i = d_b; i < d; i++) b[i] = 0;

  // do the trials, first for Karatsuba, then for grade-school.
  // For each trial, we print the result, followed by the time
  // taken per multiplication, followed by the number of
  // multiplications done. We do as many multiplications as we
  // can until we pass away an entire second.
  karatsuba(a, b, r, d); // compute product w/o regard to carry
  doCarry(r, 2 * d); // now do any carrying

  printNum(r, 2 * d);

  return 0;
}

// ret must have space for 6d digits.
// the result will be in only the first 2d digits
// my use of the space in ret is pretty creative.
// | ar*br  | al*bl  | asum*bsum | lower-recursion space | asum | bsum |
//  d digits d digits  d digits     3d digits              d/2    d/2
void
karatsuba(int *a, int *b, int *ret, int d) {
  int             i;
  int             *ar = &a[0]; // low-order half of a
  int             *al = &a[d/2]; // high-order half of a
  int             *br = &b[0]; // low-order half of b
  int             *bl = &b[d/2]; // high-order half of b
  int             *asum = &ret[d * 5]; // sum of a's halves
  int             *bsum = &ret[d * 5 + d/2]; // sum of b's halves
  int             *x1 = &ret[d * 0]; // ar*br's location
  int             *x2 = &ret[d * 1]; // al*bl's location
  int             *x3 = &ret[d * 2]; // asum*bsum's location

  // when d is small, we're better off just reverting to
  // grade-school multiplication, since it's faster at this point.
  if(d <= KARAT_CUTOFF) {
    gradeSchool(a, b, ret, d);
    return;
  }

  // compute asum and bsum
  for(i = 0; i < d / 2; i++) {
    asum[i] = al[i] + ar[i];
    bsum[i] = bl[i] + br[i];
  }

  // do recursive calls (I have to be careful about the order,
  // since the scratch space for the recursion on x1 includes
  // the space used for x2 and x3)
  karatsuba(ar, br, x1, d/2);
  karatsuba(al, bl, x2, d/2);
  karatsuba(asum, bsum, x3, d/2);

  // combine recursive steps
  for(i = 0; i < d; i++) x3[i] = x3[i] - x1[i] - x2[i];
  for(i = 0; i < d; i++) ret[i + d/2] += x3[i];
}

void
gradeSchool(int *a, int *b, int *ret, int d) {
  int             i, j;

  for(i = 0; i < 2 * d; i++) ret[i] = 0;
  for(i = 0; i < d; i++) {
    for(j = 0; j < d; j++) ret[i + j] += a[i] * b[j];
  }
}

void
doCarry(int *a, int d) {
  int             c;
  int             i;

  c = 0;
  for(i = 0; i < d; i++) {
    a[i] += c;
    if(a[i] < 0) {
      c = -(-(a[i] + 1) / 10 + 1);
    } else {
      c = a[i] / 10;
    }
    a[i] -= c * 10;
  }
  if(c != 0) fprintf(stderr, "Overflow %d\n", c);
}

void
getNum(int *a, int *d_a) {
  int             c;
  int             i;

  *d_a = 0;
  while(true) {
    c = getchar();
    if(c == '\n' || c == EOF) break;
    if(*d_a >= MAX_DIGITS) {
      fprintf(stderr, "using only first %d digits\n", MAX_DIGITS);
      while(c != '\n' && c != EOF) c = getchar();
    }
    a[*d_a] = c - '0';
    ++(*d_a);
  }
  // reverse the number so that the 1's digit is first
  for(i = 0; i * 2 < *d_a - 1; i++) {
    c = a[i], a[i] = a[*d_a - i - 1], a[*d_a - i - 1] = c;
  }
}

void
printNum(int *a, int d) {
  int i;
  for(i = d - 1; i > 0; i--) if(a[i] != 0) break;
  for(; i >= 0; i--) printf("%d", a[i]);
  printf("\n");
}