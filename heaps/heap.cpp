#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>


/**********************************************************************
 * TYPEDEFS
 **********************************************************************/

typedef unsigned int uint;

/**********************************************************************
 * FORWARD DECLARATIONS - for heap manipulation Functions
 **********************************************************************/

void AddToHeap(std::vector<uint>& heap, uint value);

uint PopFromHeap(std::vector<uint>& heap);



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

/**Read and perform the "heap operations" detailed inside input stream.
 *
 * The input file has the following format:
 *
 * <k: ammount of numbers to insert in the heap>
 * <first number...>
 *         .
 *         .
 *         .
 * <k-th number to be inserted>
 * <j: ammount of numbers to insert in the heap>
 * <first number...>
 * <j-th number>
 *         .
 *         .
 *         .
 *
 *
 * We call each of these
 *
 * 	<number of elements to be inserted><elements>*
 *
 * a "set of inputs". The input stream will consist in series of said sets.
 *
 * After a set of input numbers, the top element of the heap will be removed
 * and output to the "output stream".  Observe that if a set has 0
 * elements to be inserted, no insertion will be performed in the
 * heap (obviously) but nevertheless a removal *will* be done.
 *
 * The contents of every removal from the heap will be written to the output
 * stream, one number per line.
 *
 * @param input Stream with series of sets of input.
 * @param output Stream where removed number will be written.
 * @param heap Vector where our heap is inserted. Remember: although
 * 	C/C++ vectors and arrays start at position 0, all vector addressing
 * 	done by this algorithm assumes that addressing starts at position 1.
 * 	In order for this to be feasible, the first element of the vector
 * 	is always present (just a place-holder) and ignored.
 *
 * @warning We only perform I/O checks when reading the number of elements in
 * 	a set of inputs.
 *
 */
void HandleHeapInput(std::ifstream& input, std::ofstream& output,
		std::vector<uint>& heap)
{
	uint n;	// Number of insertions to be performed
	uint e;	// Element to be inserted into (or removed from) the heap

	// Setup vector for use as our heap container.
	heap.clear();
	// We start addressing elements from position 1. Add place-holder...
	heap.push_back(0);

	while (input >> n) {
		// Insert elements...
		for(uint i = 0; i < n; ++i) {
			input >> e;
			AddToHeap(heap, e);
		}
		e = PopFromHeap(heap);
		output << e << std::endl;
	}
}


/**********************************************************************
 * HEAP IMPLEMENTATION
 *
 * This is a min-heap implentation, i.e., it PopFromHeap() returns
 * the smallest element stored in the heap.
 *
 * Additionally, attention should be paid to the way we address heaps elements.
 * Differently from what is common in C/C++ implementations, the first
 * element of the heap is available in heap[1], and not as heap[0].
 * More  information on this issue in the documentation HeapSize(),
 * AddToHeap(), and PopFromHeap().
 *
 **********************************************************************/


/**Return the number of elements in the heap.
 *
 * Remember: heap[0] is not used by our algorithm and we expect
 * heap.size() >= 1 even if the heap is empty!
 *
 * The result of this function can be directly used as an index for vector
 * addressing, i.e., the last element in the heap is heap[HeapSize(heap)].
 */
inline ssize_t HeapSize(const std::vector<uint>& heap)
{
	if (heap.size() < 0) {
		return 0;
	}
	return heap.size() - 1;
}


/** Add an element to a heap.
 *
 * @param heap The heap, as a vector. Its first (and smallest) element
 * 	is available at heap[1]. Notice that heap[0] is not used
 * 	here -- just to ease the algorithm.
 *
 * @param value to be inserted into the heap.
 *
 */
void AddToHeap(std::vector<uint>& heap, uint value)
{
	// Add element to heap's tail and "heapify-up",
	// from leaves to the root (heap[1]).
	heap.push_back(value);
	ssize_t pos = HeapSize(heap); // last element
	ssize_t parent = pos / 2;
	while(heap[parent] > heap[pos] && pos > 1) {
		std::swap(heap[parent], heap[pos]);
		pos = parent;
		parent = pos / 2;
	}

}

/**Pop the smallest element from the heap and return it.
 *
 * If the heap is empty, then 0 will returned.
 *
 */
uint PopFromHeap(std::vector<uint>& heap)
{
	ssize_t last = HeapSize(heap);
	if (last == 0) {
		return 0;
	}

	// Get element from the heap's head, move it to heap's tail,
	// remove it...
	uint res = heap[1];
	std::swap(heap[1], heap[last]);
	heap.pop_back();

	// ... and "heapify-down", from root (heap[1]) to leaves.
	ssize_t current_pos = 1;
	ssize_t left_child_pos, right_child_pos;
	while (true) {
		uint& current = heap[current_pos]; // Handy alias
		left_child_pos = 2 * current_pos;
		right_child_pos = 2 * current_pos + 1;
		// Check if heap property is valid...
		if (right_child_pos <= HeapSize(heap)) {
			// Current node has two children
			// Let's create two handy aliases for them
			uint& left_child = heap[left_child_pos];
			uint& right_child = heap[right_child_pos];
			// Check if the smallest child is smaller than
			// the parent and, if it is, swap'em
			if (left_child < right_child) {
				if (left_child < current) {
					std::swap(left_child, current);
					current_pos = left_child_pos;
				} else {
					// OK. Heap property held.
					break;
				}
			} else {
				if (right_child < current) {
					std::swap(right_child, current);
					current_pos = right_child_pos;
				} else {
					// OK. Heap property held.
					break;
				}
			}
		} else if (left_child_pos <= HeapSize(heap)) {
			// Current node has only one child - the left child
			uint& left_child = heap[left_child_pos];
			if (left_child < current) {
				std::swap(left_child, current);
				current_pos = left_child_pos;
			} else {
				// OK. Heap property held.
				break;
			}
		} else {
			// Current node doesn't have a child -- it is a leaf.
			// OK. Heap property held.
			break;
		}
	}

	return res;
}



/**********************************************************************
 * MAIN APP LOGIC
 **********************************************************************/


int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cerr << "ERROR: Wrong number of arguments.\n" <<
			     "Usage: ./heap INPUT OUTPUT\n" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream input;
	std::ofstream output;
	

	// Limiting automatic I/O error-checking to output.
	TurnExceptionsOn(output);

	input.open(argv[1]);
	if (!input) {
		std::cerr << "Error opening input file '" << argv[1] <<
			"'" << std::endl;
	}
	output.open(argv[2]);

	std::vector<uint> heap;
	// Reserve some space for the vector in advance and avoid
	// run-time reallocation penalities.
	// XXX Adjust to match available memory XXX
	// XXX Adjust to match available memory XXX
	// XXX Adjust to match available memory XXX
	const ssize_t MAX_MEMORY = 1 * (1 << 30); // 1 Gigabyte of RAM
	heap.reserve( MAX_MEMORY  / sizeof(uint));

	HandleHeapInput(input, output, heap);

	return EXIT_SUCCESS;
}
