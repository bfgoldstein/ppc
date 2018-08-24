typedef struct {
	long unsigned int weight;
	long unsigned int volume;
} item;
/**
 * @param argc the argc
 * @param argv the argv
 * @param output The output array of item quantities
 * @param capacity The knapsack capacity
 * @param n The number of available items
 * @param items The array of n available items
 */
void knapsack(int argc,char* argv[],long unsigned int* output,const long unsigned int capacity,const long unsigned int n,const item* items);
