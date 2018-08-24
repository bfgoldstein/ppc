#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100010
#define LEN 25001

char seq[MAX][LEN];

void add(int a, int b) {
	int i, aux, s;

	for (i = 0, aux = 0; seq[a][i] != '\0' && seq[b][i] != '\0'; i++) {
		s = seq[a][i] + seq[b][i] + aux - '0' - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
	}

	while (seq[a][i] != '\0') {
		s = seq[a][i] + aux - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
		i++;
	}

	while (seq[b][i] != '\0') {
		s = seq[b][i] + aux - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
		i++;
	}

	if (aux != 0)
		seq[a + 1][i++] = aux + '0';
	seq[a + 1][i] = '\0';
}

int main() {
	int n, i, len;

	seq[0][0] = '0';
	seq[0][1] = '\0';
	seq[1][0] = '1';
	seq[1][1] = '\0';
	for (i = 2; i < MAX; i++)
		add(i - 1, i - 2);

	scanf("%d", &n);

	len = strlen(seq[n]);
	for (i = 0; i <= len - 1; i++)
		printf("%c", seq[n][len - 1 - i]);
	printf("\n");
	fflush(stdout);

	return 0;
}
