#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int nNodes;
short int* graph;

void warshall();
void read();
void write(FILE *fl);

void write(FILE *fl){
  int i, j;

  for( i=0; i<nNodes; i++ ){
    for( j=0; j<nNodes; j++ )
      fprintf( fl, "%d ", graph[i * nNodes + j] );

    fprintf( fl, "\n");
  }
}

void read (){

  char line[50];
  char* token;
  int size = 50;

  int l;
  int c;

  fgets(line,size,stdin);

  while(!feof(stdin)){

    token = strtok(line," "); // split using space as divider
    if(*token == 'p') {

      token = strtok(NULL," "); // sp

      token = strtok(NULL," "); // no. of vertices
      nNodes = atoi(token);

      token = strtok(NULL," "); // no. of directed edges

      graph = (short int*) malloc(nNodes * nNodes * sizeof (short int));
      if (graph == NULL) {
        printf( "Error in graph allocation: NULL!\n");
        exit( EXIT_FAILURE);
      }

      for(int i = 0; i < nNodes;i++){
        for(int j = 0; j < nNodes;j++){
          graph[i*nNodes+j] = 0;
        }
      }

    } else if(*token == 'a'){
      token = strtok(NULL," ");
      l = atoi(token)-1;

      token = strtok(NULL," ");
      c = atoi(token)-1;

      token = strtok(NULL," ");
      graph[l*nNodes+c] = 1;

    }

    fgets(line,size,stdin);
  }
}


void warshall(){

  for (int k = 0; k < nNodes; k++){
    for (int i = 0; i < nNodes; i++){
      for (int j = 0; j < nNodes; j++){

        if(graph[i * nNodes + k] + graph[k * nNodes + j] < graph[i * nNodes + j])
          graph[i * nNodes + j] = 1;

      }
    }
  }

}

int main( int argc, char *argv[] ){

  read();
  warshall();
  write(stdout);

  free(graph);

  return 0;
}

