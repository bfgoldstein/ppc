#include <stdlib.h>
#include <string.h>
#include "bucketsort.h"

#define N_BUCKETS 94

typedef struct {
	long int *data;
	int length;
	long int total;
} bucket;

void sort(char *a, bucket *bucket) {
	int j, i, length;
	long int key;
	length = bucket->length;
	for (j = 1; j < bucket->total; j++) {
		key = bucket->data[j];
		i = j - 1;
		while (i >= 0
				&& strcmp(a + bucket->data[i] * length, a + key * length) > 0) {
			bucket->data[i + 1] = bucket->data[i];
			i--;
		}
		bucket->data[i + 1] = key;
	}
}

long int* bucket_sort(char *a, int length, long int size) {

	long int i;
	bucket buckets[N_BUCKETS], *b;
	long int *returns;

	// allocate memory
	returns = malloc(sizeof(long int) * size);
	for (i = 0; i < N_BUCKETS; i++) {
		buckets[i].data = returns + i * size / N_BUCKETS;
		buckets[i].length = length;
		buckets[i].total = 0;
	}

	// copy the keys to "buckets"
	for (i = 0; i < size; i++) {
		b = &buckets[*(a + i * length) - 0x21];
		b->data[b->total++] = i;
	}

	// sort each "bucket"
	for (i = 0; i < N_BUCKETS; i++)
		sort(a, &buckets[i]);

	return returns;
}
