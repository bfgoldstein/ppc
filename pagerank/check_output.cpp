#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>
#include <limits>
#include <cmath>
#include <stdlib.h>

/**********************************************************************
 * TYPEDEFS
 * CONSTANT DEFINITIONS
 **********************************************************************/

typedef unsigned int uint;


//! We stop refining PageRank calculations if the accumulated residual
//! difference between iterations get smaller than this value
const float PAGERANK_RESIDUAL_LIMIT = 0.001; 


/**********************************************************************
 * INPUT AND OUTPUT FUNCTIONS
 **********************************************************************/


/**Turn on exception reporting for a streams
 *
 * Any read or writing error on stream will raise an exception -- no error
 * will be mistakenbly silenced!
 */
template <class _STREAM> void TurnExceptionsOn(_STREAM& stream)
{
	stream.exceptions(std::ios_base::badbit |
			  std::ios_base::failbit |
			  std::ios_base::eofbit);
}

//!Reads pagerank ouput
void ReadPageRankOutput(std::ifstream& input, std::valarray<float>& pagerank)
{
	uint n_nodes;
	float value;

	TurnExceptionsOn(input);

	// Number of nodes
	input >> n_nodes;

	// Clear PageRanks - setup PageRank vector with initial values
	if (pagerank.size() != n_nodes) {
		pagerank.resize(n_nodes);
	}
	pagerank = 0.0;

	// Read pagerank values
	for (uint i = 0; i < n_nodes; ++i) {
		input >> value;
		pagerank[i] = value;
	}
}


/**********************************************************************
 * MAIN APP LOGIC
 **********************************************************************/


/**Calculate the L1 Norm of the difference between the PageRank values
 * found between to consecutive iterations.
 */
float CalculateL1Norm(const std::valarray<float>& old_pageranks,
		      const std::valarray<float>& new_pageranks)
{
	std::valarray<float> diff = abs(new_pageranks - old_pageranks);
	return diff.sum();
}


int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "ERROR: Wrong number of arguments.\n" <<
			     "Usage: ./pr OUTPUT_USER OUTPUT_REFERENCE" <<
			     std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream output_user;
	std::ifstream output_ref;
	std::valarray<float> pagerank_user;
	std::valarray<float> pagerank_ref;
	float residual = 1.0;

	TurnExceptionsOn(output_user);
	TurnExceptionsOn(output_ref);

	output_user.open(argv[1]);
	output_ref.open(argv[2]);

	ReadPageRankOutput(output_user, pagerank_user );
	ReadPageRankOutput(output_ref, pagerank_ref );
	if (pagerank_user.size() != pagerank_ref.size()) {
		std::cout << "ERROR: User and reference output differ " <<
			     "in length." << std::endl;
		exit(EXIT_FAILURE);
	}

	residual = CalculateL1Norm(pagerank_user, pagerank_ref);
	if (residual < 2 * PAGERANK_RESIDUAL_LIMIT) {
		// Yeah, we are kinda benevolent.
		std::cout << "OK: user and reference output are not " <<
			"too distant." << std::endl;
		exit(EXIT_SUCCESS);
	} else {
		std::cout << "ERROR: User and reference output differ " <<
			     "too much." << std::endl;
		exit(EXIT_FAILURE);
	}
}
