// 《人教版高中数学必修4》
// p151，利用信息技术制作三角函数表

#include <stdio.h>
#include <math.h>

const double PI = 3.141592653;
const MAX_MOA = 5400;

double degree2ratio(double degree)
{
	return degree * PI / 180;
}

double sind(double degree)
{
	return sin(degree2ratio(degree));
}

double cos_by_sin(double sval)
{
	return sqrt(1 - sval * sval);
}

int main()
{
	// moa: minute of angle，角分
	double sin1moa = sind(1.0 / 60);
	double cos1moa = cos_by_sin(sin1moa);

	printf("sin 0° 1'=%.9lf\n", sin1moa);

	double sin_an = sin1moa;
	double cos_an = cos1moa;

	for (int moa = 2; moa <= MAX_MOA; moa++) {
		sin_an = sin1moa * cos_an + cos1moa * sin_an;
		cos_an = cos_by_sin(sin_an);		
		printf("sin%2d°%2d'=%.9lf    %.9lf\n", moa / 60, moa % 60, sin_an, sind(moa / 60.0));
	}

}
