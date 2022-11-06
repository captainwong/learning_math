#include <stdio.h>
#include <math.h>

typedef double(*Function)(double x);

// 牛顿法求方程近似解
// function 求函数值
// derivative 求导数
// x0 初值
// precision 精度
double newton(Function function, Function derivative, double x0, double precision)
{
	double z = precision;
	double x1 = x0;

	while (z <= precision) {
		x1 = x0 - function(x0) / derivative(x0);
		z = fabs((x1 - x0) / x0);
		x0 = x1;
	}

	return x1;
}

double f(double x) {
	return pow(x, 3) + 2 * x * x + 10 * x - 20;
}

double d(double x) {
	return 3 * x * x + 4 * x + 10;
}

int main()
{
	printf("%lf\n", newton(f, d, 4, 0.000001));
}