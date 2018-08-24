#include <set>
#include <map>

using namespace std;

/**
 * @param argc the argc 
 * @param argv the argv 
 * @param clique2 the input graph (edges)
 * @param n the number of nodes
 * @param output the output set of maximal cliques
 */
void clique(int argc, char** argv, set<set<unsigned int> >& output, const set<set<unsigned int> >& clique2, const unsigned int n);
