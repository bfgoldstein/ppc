#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>
#include <limits>
#include <cmath>
#include <stdlib.h>

/**********************************************************************
 * TYPEDEFS
 **********************************************************************/

typedef unsigned int uint;

//! List of outlinks for a given node
typedef std::vector<uint> outlinks_t;

//! List of nodes (and theirs oulinks)
typedef std::vector<outlinks_t> nodes_outlinks_t;

//! List of PageRank results FIXME NOT USED
typedef std::valarray<float> nodes_pagerank_t;


/**********************************************************************
 * CONSTANT DEFINITIONS
 **********************************************************************/


//! Initial (or default) value for PageRank Calculations
const float PAGERANK_SEED_VALUE = 1.0;

//! We stop refining PageRank calculations if the accumulated residual
//! difference between iterations get smaller than this value
const float PAGERANK_RESIDUAL_LIMIT = 0.001; 

//! PageRank's "damping factor", i.e, the probability at each page the
//! "random surfer" will get bored and request another random page.
const float PAGERANK_D = 0.85;


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

/**Reads the list of nodes and theis outlinks.
 *
 * In the file, the first line has the number of nodes in the graph.
 * The 1st line has the number of outlinks from node 0 followed by the list
 * of said outlinks, separated by space. The 2nd line has the number of
 * outlinks for node 1 and so on...
 *
 * @param input Stream with a list of nodes and their contents
 * @param nodes List of nodes (and their outlinks). The contents of
 * 	input will be parsed and read into this list.
 *
 * @warning Failure during I/O will result in exceptions being thrown.
 *
 */
void ReadOutlinkLists(std::ifstream& input, nodes_outlinks_t& nodes)
{
	uint n_nodes;
	uint n_outlinks;

	TurnExceptionsOn(input);

	// Number of nodes
	input >> n_nodes;
	// Setup a new list with n nodes -- and n empty outlinks lists
	nodes_outlinks_t read_nodes(n_nodes);
	// Read each node's outlinks list
	for (uint i = 0; i < n_nodes; ++i) {
		input >> n_outlinks;
		outlinks_t& outlinks = read_nodes[i];  // Creating an alias...
		for (uint j = 0; j < n_outlinks; ++j) {
			uint link;
			input >> link;
			outlinks.push_back(link);
		}
	}
	// Ok, read all nodes.
	// Replace old content in nodes by the contents of read_nodes;
	nodes.swap(read_nodes);
}


/**Outputs the PageRank values for a group of nodes to a stream.
 *
 * The first line of the stream will have the number of nodes.
 * The next line will have the value for node 0, the following for
 * node 1 and so on... 
 *
 * @param output Where the list of PageRank values will be written.
 * @param ranks The list of PageRanks value;
 *
 * @warning any error during output will result in an exception being thrown.
 */
template<class _OUT>void OutputPageRanks(_OUT& output, std::valarray<float> ranks)
{
	output << ranks.size() << std::endl;
	for (uint i = 0; i < ranks.size(); ++i) {
		output << ranks[i] << std::endl; 
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


/**Calculate the PageRank value for a list of nodes.
 *
 * PageRank Formula (in tex):
 *
 * PR(i) = (1-d) + d\sum_{v \in B_i}\frac{PR(v)}{N_v}
 *
 * Where:
 *
 *  PR(i): PageRank for node i
 *  d: damping factor, the probability at each page the "random surfer"
 *  	will get bored and request another random page.
 *  B_i, or B(i): set of pages that have links pointing to i
 *  N_v, or N(v): number of outlinks node v has.
 *
 *
 * @param nodes List of nodes -- and their outlinks
 *
 * @param rank PageRank values for every node. The result of the calculation
 * 	will be returned though this vector
 */
void CalculatePageRank(const nodes_outlinks_t& nodes,
		std::valarray<float>& pagerank)
{
	float residual = std::numeric_limits<float>::max(); // MAX_FLOAT
	float vote_value = 0.0;
	const float d = PAGERANK_D;


	// Clear PageRanks - setup PageRank vector with initial values
	if (pagerank.size() != nodes.size()) {
		pagerank.resize(nodes.size());
	}
	pagerank = PAGERANK_SEED_VALUE;
	// Setup accumulator for intermediate values;
	// Notice: valarray constructor differs from other containers
	// in that its format is (defalt_value, n elements)
	std::valarray<float> acc(0.0, nodes.size());

	// While not converged
	while (residual > PAGERANK_RESIDUAL_LIMIT) {
		// For each node, calculate its contribution to other nodes' 
		// PageRank and accumulate it in acc
		for (uint i = 0; i < pagerank.size(); ++i) {
			const outlinks_t& outlinks = nodes[i]; // Alias...
			// No outlinks?
			if (!outlinks.empty()) {
				// Account for this node vote value... 
				vote_value = pagerank[i]/outlinks.size();
				// ... in its outlinks' PageRank
				for (uint u = 0; u < outlinks.size(); ++u) {
					acc[outlinks[u]] += vote_value;
				}
			}
		}
		// Do last part of PR estimation loop
		// For each node, PR[i] = (1-d) + d*(sum of accumulated pr)
		acc *= d;		// applied to every element in acc
		acc += (1.0 - d);	// ditto ^^
		// Get residual error
		residual = CalculateL1Norm(pagerank, acc);
		// Update Page rank, reset accumulators
		pagerank = acc;
		acc = 0.0;
	}
}



int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "ERROR: Wrong number of arguments.\n" <<
			     "Usage: ./pr INPUT OUTPUT\n" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream input;
	std::ofstream output;
	nodes_outlinks_t nodes;
	

	TurnExceptionsOn(input);
	TurnExceptionsOn(output);

	input.open(argv[1]);
	output.open(argv[2]);

	ReadOutlinkLists(input, nodes);
	std::valarray<float> ranks(nodes.size());
	CalculatePageRank(nodes, ranks);
	OutputPageRanks(output, ranks);
}
