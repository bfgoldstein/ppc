#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

static unsigned long int next = 1;

int my_rand(void) {
	return ((next = next * 1103515245 + 12345) % ((u_long) RAND_MAX + 1));
}

void my_srand(unsigned int seed) {
	next = seed;
}

struct Graph {
	int nNodes;
	int *nEdges;
	int **edges;
	int **w;
};

struct Graph *createRandomGraph(int nNodes, int nEdges, int seed) {
	my_srand(seed);

	struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
	graph->nNodes = nNodes;
	graph->nEdges = (int *) malloc(sizeof(int) * nNodes);
	graph->edges = (int **) malloc(sizeof(int *) * nNodes);
	graph->w = (int **) malloc(sizeof(int *) * nNodes);

	int k, v;
	for (v = 0; v < nNodes; v++) {
		graph->edges[v] = (int *) malloc(sizeof(int) * nNodes);
		graph->w[v] = (int *) malloc(sizeof(int) * nNodes);
		graph->nEdges[v] = 0;
	}

	int source = 0;
	for (source = 0; source < nNodes; source++) {
		int nArestasVertice = (double) nEdges / nNodes
				* (0.5 + my_rand() / (double) RAND_MAX);
		for (k = nArestasVertice; k >= 0; k--) {
			int dest = my_rand() % nNodes;
			int w = 1 + (my_rand() % 10);
			graph->edges[source][graph->nEdges[source]] = dest;
			graph->w[source][graph->nEdges[source]++] = w;
		}
	}

	return graph;
}

int *dijkstra(struct Graph *graph, int source) {
	int nNodes = graph->nNodes;
	int *visited = (int *) malloc(sizeof(int) * nNodes);
	int *distances = (int *) malloc(sizeof(int) * nNodes);
	int k, v;

	for (v = 0; v < nNodes; v++) {
		distances[v] = INT_MAX;
		visited[v] = 0;
	}
	distances[source] = 0;
	visited[source] = 1;
	for (k = 0; k < graph->nEdges[source]; k++)
		distances[graph->edges[source][k]] = graph->w[source][k];

	for (v = 1; v < nNodes; v++) {
		int min = 0;
		int minValue = INT_MAX;
		for (k = 0; k < nNodes; k++)
			if (visited[k] == 0 && distances[k] < minValue) {
				minValue = distances[k];
				min = k;
			}

		visited[min] = 1;

		for (k = 0; k < graph->nEdges[min]; k++) {
			int dest = graph->edges[min][k];
			if (distances[dest] > distances[min] + graph->w[min][k])
				distances[dest] = distances[min] + graph->w[min][k];
		}
	}

	free(visited);

	return distances;
}

int main(int argc, char ** argv) {

	int nNodes;
	int nEdges;
	int seed;

	if (argc == 4) {
		nNodes = atoi(argv[1]);
		nEdges = atoi(argv[2]);
		seed = atoi(argv[3]);
	} else {
		fscanf(stdin, "%d %d %d", &nNodes, &nEdges, &seed);
	}

	nEdges = nNodes * nEdges;

	struct Graph *graph = createRandomGraph(nNodes, nEdges, seed);

	int *dist = dijkstra(graph, 0);

	double mean = 0;
	int v;
	for (v = 0; v < graph->nNodes; v++)
		mean += dist[v];

	fprintf(stdout, "%.2f\n", mean / nNodes);

	return 0;
}
