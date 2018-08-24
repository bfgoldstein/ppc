typedef struct {
	long unsigned int x;
	long unsigned int y;
} point;
/**
 * @param argc the argc
 * @param argv the argv
 * @param h the size of the set of points on the convex hull
 * @param output the set of points on the convex hull
 * @param n the size of the set of input points
 * @param input the set of input points
 */
void convex_hull(int argc,char* argv[],long unsigned int* h,point* output,const long unsigned int n,const point* input);

