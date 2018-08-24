typedef struct {
	long unsigned int row;
	long unsigned int column;
	long unsigned int value;
} entry;

/**
 * @param ab_entries 
 * @param n the number of nodes
 * @param output the output set of maximal cliques
 */
void sparse_matrix_multiplication(long unsigned int* ab_entries,entry* ab,const long unsigned int a_rows,const long unsigned int a_columns_b_rows,const long unsigned int b_rows,const long unsigned int a_entries,const long unsigned int b_entries,const entry* a,const entry* b);

