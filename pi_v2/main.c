#include <stdlib.h>
#include <stdio.h>

void pi(char* output, const long int n, const long int d) {
	long int digits[d + 11];;
	long int digit, i;
	int signal;
	long unsigned int remainder, div, mod;

	for(digit=0;digit<d+11;++digit) {
		digits[digit]=0;
	}

	signal = 1;
	for(i=0;i<=n;++i) {
		remainder = 4;
		for(digit=0;digit<d+11&&remainder;++digit) {
			div=remainder/(2*i+1);
			mod=remainder%(2*i+1);
			digits[digit]+=(signal*div);
			remainder=mod*10;
		}
		signal *= -1;
	}

	for(i=d+11-1;i>0;--i) {
		digits[i-1]+=digits[i]/10;
		digits[i]%=10;
		if(digits[i]<0) {
			digits[i-1]--;
			digits[i]+=10;
		}
	}

	if(digits[d+1]>=5) {
		++digits[d];
	}

	for(i=d;i>0;--i) {
		digits[i-1]+=digits[i]/10;
		digits[i]%=10;
	}

	output[0] = digits[0]+'0';
	output[1]= '.';
	for(i=1;i<=d;i++)
	output[i+1] = digits[i]+'0';
	output[d+2]=0;
}

int main(int argc, char*argv[]) {

	int n, d;

	FILE *in, *out;

	in = fopen("pi.in", "r");
	out = fopen("pi.out", "w");

	fscanf(in, "%d%d", &n, &d);

	char output[d + 4];;

	pi(output, n, d);

	fprintf(out, "%s\n", output);
	fflush(out);

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}

