#include <stdio.h>
#include <math.h>

//const int MAX_N = 96;
//const int MAX_N = 1536;
const int MAX_N = 12288;

int main()
{
	double l = 1;
	for (int n = 6; n <= MAX_N; n *= 2) {
		printf("n=%d, pi=%.9lf\n", n, n * l / 2);
		l = sqrt(2 - sqrt(4 - l * l));
	}
}
