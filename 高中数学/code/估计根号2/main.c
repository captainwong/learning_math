#include <stdio.h>

int main()
{
	double a = 1;
	double d = 0.1;
	while (d > 0.000001) {
		while ((a + d) * (a + d) <= 2) {
			a += d;
		}
		printf("%lf\n", a);
		d *= 0.1;
	}
}