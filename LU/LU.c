/*****************************************************
 * Site: http://rosettacode.org/wiki/LU_decomposition
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef DEBUG
#define DEBUG 0
#endif
 
typedef double **mat;
 
void mat_zero(mat x, int n) {
  int i, j;
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      x[i][j] = 0;
    }
  }
}
 
mat mat_new(int n) {
  int i;
  mat x = malloc(sizeof(double*) * n);
  if(x == NULL)
    perror("memory failure");
  x[0]  = malloc(sizeof(double) * n * n);
  if(x[0] == NULL)
    perror("memory other failure");

  for(i=0; i<n; i++) {
    x[i] = x[0] + n * i;
  }
  mat_zero(x,n);
 
  return x;
}
 
mat mat_copy(void *s, int n) {
  int i,j;
  mat x = mat_new(n);
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      x[i][j] = ((double (*)[n])s)[i][j];
    }
  }
  return x;
}

void mat_gen(mat s, int n) {
  int i,j;
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      scanf("%lf",&s[i][j]);
    }
  }
}
 
void mat_del(mat x) {
  free(x[0]);
  free(x);
}
 
void mat_show(const mat x, const char *name, char *fmt, int n) {
  int i,j;
  if(DEBUG)
    printf("%s =",name);
  if (!fmt) fmt = "%.5lf";
  for(i=0; i<n; i++) {
   if(DEBUG)
      printf(i ? "      " : " [ ");
    for(j=0; j<n; j++) {
      printf(fmt, x[i][j]);
      if(DEBUG)
        printf(j < n - 1 ? "  " : i == n - 1 ? " ]\n" : "\n");
      else
        printf(j < n - 1 ? " " : "\n");
    }
  }
}
 
mat mat_mul(const mat a, const mat b, int n) {
  int i,j,k;
  mat c = mat_new(n);
  for(i=0; i<n; i++) {
    for(k=0; k<n; k++) {
      for(j=0; j<n; j++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}
 
void mat_pivot(mat a, mat p, int n) {
  int i,j,k;
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      p[i][j] = (i == j);
    }
  }
  for(i=0; i<n; i++) {
    int max_j = i;
    for(j=i; j<n; j++) {
      if (fabs(a[j][i]) > fabs(a[max_j][i]))
        max_j = j;
    }
    if (max_j != i) {
      for(k=0; k<n; k++) {
        double tmp;
        tmp = p[i][k];
        p[i][k] = p[max_j][k];
        p[max_j][k] = tmp;
      }
    }
  }
}
 
void mat_LU(mat A, mat L, mat U, mat P, int n) {
  int i,j,k;
  mat_zero(L,n);
  mat_zero(U,n);
  mat_pivot(A, P, n);
 
  mat Aprime = mat_mul(P, A, n);

  for(i=0; i<n; i++) {
    L[i][i] = 1;
  }
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      double s;
      if (j <= i) {
        s=0;
        for(k=0; k<j; k++) {
          s += L[j][k] * U[k][i];
        }
        U[j][i] = Aprime[j][i] - s;
      }
      if (j >= i) {
        s=0;
        for(k=0; k<i; k++) {
          s += L[j][k] * U[k][i];
        }
        L[j][i] = (Aprime[j][i] - s) / U[i][i];
      }
    }
  }
 
  mat_del(Aprime);
}
 
int main() {
  int n;
  mat A, L, P, U;

  fscanf(stdin,"%d",&n);
  A = mat_new(n);
  L = mat_new(n);
  P = mat_new(n);
  U = mat_new(n);

  mat_gen(A,n);

  mat_LU(A, L, U, P, n);

  mat_show(P,"P",0,n);
  printf("\n");
  mat_show(L,"L",0,n);
  printf("\n");
  mat_show(U,"U",0,n);

  mat_del(A); 
  mat_del(L);
  mat_del(U);
  mat_del(P);
 
  return 0;
}

