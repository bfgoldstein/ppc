#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

typedef unsigned int uint;

template <class _STREAM> void TurnExceptionsOn(_STREAM& stream)
{
	stream.exceptions(std::ios_base::badbit |
			  std::ios_base::failbit |
			  std::ios_base::eofbit);
}

/**Read the list of parents from a input stream
 *
 * Given a forest G = {V,E}.
 * The list of parents, P, is such that, for a given node i,
 * 0 <= i < n, P[i] = j IFF (i,j) exists in E. If 'i' is a root
 * node then P[i] = i.
 *
 * @param input An input stream from where the list of parents will be read.
 * 	The first line of this stream is the number of elements in the list.
 * @param P, a vector where the list of parents will be stored. Must be
 * 	allocated and non-NULL.
 *
 */
void ReadParentList(std::istream& input, std::vector<uint>& P)
{
	uint n;
	uint val;

	TurnExceptionsOn(input);
	// Read the number of elements
	input >> n;
	P.reserve(n);
	P.clear();
	// Read the elements
	for (unsigned int i = 0; i < n; ++i) {
		input >> val;
		P.push_back(val);
	}
}

/**Recursivelly finds the root of the tree where a node is.
 *
 * @param i A node. We will find the root of the tree this node belongs to.
 * @param S A list of roots. At the start of the algorithm, S may be filled
 * 	with a list of parents but, during execution we will update this list
 * 	to the list of roots. At the end of the algorithm, this list will
 * 	contain the list of root.
 */
uint FindRootOfNode(unsigned int i, std::vector<uint>& S)
{
	if (S[i] != S[S[i]] ) {
		S[i] = FindRootOfNode(S[i], S);
	}

	return S[i];
}


/**Finds the roots of a forest.
 *
 * The graph is contained in the vector P, a list of parents.
 *
 * @param P The list of parents nodes for every node in the graph.
 * @param S The list of roots. For any node i, 0 <= i < n. S[i] returns
 * 	the root of the tree where i belongs.
 *
 */
void FindRoots(const std::vector<uint>& P, std::vector<uint>& S)
{
	const uint n = P.size();

	// Copy P to S
	S.clear();
	S.reserve(n);
	S.insert(S.begin(), P.begin(), P.end());

	for (unsigned int i = 0; i < n; ++i) {
		S[i] = FindRootOfNode(i, S);
	}
}

void WriteRootList(std::ofstream& output, std::vector<uint> S)
{
	output << S.size() << std::endl;
	for(uint i = 0; i < S.size(); ++i) {
		output << S[i] << std::endl;
	}
}


int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "Wrong number of elements.\n" << 
			  "Usage: roots_of_a_forest INPUT OUTPUT" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream input;
	std::ofstream output;
	std::vector<uint> parents;
	std::vector<uint> roots;

	TurnExceptionsOn(input);
	TurnExceptionsOn(output);

	input.open(argv[1]);
	output.open(argv[2]);

	ReadParentList(input, parents);
	FindRoots(parents, roots);
	WriteRootList(output, roots);

}
