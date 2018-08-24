#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

/**********************************************************************
 * TYPEDEFS
 **********************************************************************/

typedef unsigned int uint;

/**********************************************************************
 * INPUT AND OUTPUT FUNCTIONS
 **********************************************************************/


/**Turn on exception reporting for a stream
 *
 * Any read or write error on stream will raise an exception -- no error
 * will be mistakenbly silenced!
 */
template <class _STREAM> void TurnExceptionsOn(_STREAM& stream)
{
        stream.exceptions(std::ios_base::badbit |
                          std::ios_base::failbit |
                          std::ios_base::eofbit);
}


/**Make a N x N matrix.
 *
 * Care must be taken free'ing matrixes create using this function.
 * Correction: just don't delete[] this matrix. If you **REALLLY** want
 * to free this matrix you've got to proceed as follows:
 *
 * 	uint** M = makeSquareMatrix(n); 
 * 	uint* store = &M[0][0]
 * 	uint* M_rows = &M[0]; 
 * 	delete[] store;
 * 	delete[] M_rows;
 *
 * @eturn The square matrix or NULL on non-fatal errors.
 *
 * @warning May throw an exception if allocation fails.
 */
uint** makeSquareMatrix(uint n)
{
	if (n == 0) {
		return NULL;
	}

	uint** B = NULL;
	uint* store = NULL;

	// Allocate matrix
	store = new uint[n*n];
	// Clear it...
	memset(store, 0x00, n * n * sizeof(int));
	// Setup array B
	B = (uint**) new uint[n];
	for (int row = 0; row < n; ++row) {
		B[row] = &store[row * n];
	}

	return B;

}

/***Read a undirected graph from @p input
 *
 * @param input Stream from where the graph is read.
 * @param n nunber of nodes in the graph. It is returned by reference to
 * 	the callee.
 *
 * @return A incidence matrix (square matrix w/ n rows) with the graph.
 *
 * @warning Errors reading the number of nodes in the graph will throw an
 * 	exception.
 */
uint** readFile(std::istream& input, uint& n)
{
	uint** M = NULL;
	uint u, v, k;

	// Read number of nodes -- MUST be in input's first line 
	// If any error occour while we read the first line, throw an exception
	n = 0;
	TurnExceptionsOn(input);
	input >> n;
	// Turned Exception Reporting OFF - it was kinda silly but whatever.
	input.exceptions(std::ios_base::goodbit);
	// Allocate matrix
	M = makeSquareMatrix(n);
	if (M == NULL) {
		return NULL;
	}
	// Read graph;
	while (input >> u >> v >> k) {
		M[u][v] = k;
		M[v][u] = k;
	}

	return M;
}


/**********************************************************************
 * MAIN ALGORITHM
 **********************************************************************/


double findClusterCoefficient(uint** M, uint n)
{
	double partial_cc = 0.0;
	std::vector<uint> neighbors;

	neighbors.reserve(n);

	// For each node
	for (uint i = 0; i < n; ++i) {
		// Set things up for this iteration
		neighbors.clear();
		uint n_triangles = 0;
		// Finds i's neighborhood
		for (uint j = 0; j < n; ++j) {
			if ( i != j && M[i][j]) {
				neighbors.push_back(j);
			}
		}
		// Find the number of clusters in i's neighborhood
		if (neighbors.size() < 2) {
			// At least two neighbors are need in order to
			// be able to calc. i's Clustering Coefficient
			continue;
		}
		const uint nei_len = neighbors.size();
		for (uint j = 0; j < nei_len; ++j) {
			uint u = neighbors[j];
			for (uint k = j; k < nei_len; k ++) {
				uint v = neighbors[k];
				if (M[u][v]) {
					++n_triangles;
				}
			}
		}
		// Remember: The graph is undireted, so M[u][v] is treated as
		// being equivalent to M[v][u]. But in the loop above we only
		// accounted for one of those edges (namely, M[u][v]). Thus
		// n_triangles should be doubled.
		// Also notice that the maximum number of clusters between
		// i's neighbors is nei_len * (nei_len - 1)
		partial_cc += 2 * n_triangles / double(nei_len * (nei_len - 1));
	}

	return partial_cc / n;
}



/**********************************************************************
 * MAIN APP LOGIC
 **********************************************************************/


int main(int argc, char* argv[])
{
	uint** matrix = NULL;
	uint n;

        std::ifstream input;
        std::ofstream output;

	TurnExceptionsOn(input);
	TurnExceptionsOn(output);

	if (argc != 3) {
                std::cerr << "ERROR: Wrong number of arguments.\n" <<
                             "Usage: ./clustering_coefficient INPUT OUTPUT\n" 
			     << std::endl;
                exit(EXIT_FAILURE);
	}

	input.open(argv[1]);  
	output.open(argv[2]);

	matrix = readFile(input, n);
	if (matrix == NULL) {
		std::cerr << "Error creating square matrix" << std::endl;
		return 1;
	}

	float clustering_coefficient = findClusterCoefficient(matrix, n);
	output << clustering_coefficient << std::endl;
}
