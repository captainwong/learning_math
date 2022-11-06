// 必修1 用二分法求方程的近似解

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 求函数值
typedef double(*Function)(double x);

// 二分法求方程f在[a,b]的近似解，精确度epsilon
double bisection(Function f, double a, double b, double epsilon)
{
	double fa = f(a);
	double fb = f(b);
	if (fa == 0) {
		return a;
	}
	if (fb == 0) {
		return b;
	}

	if (fa * fb > 0) {
		fprintf(stderr, "f(a) * f(b) > 0\n");
		exit(1);
	}

	while (1) {
		double x1 = (a + b) / 2.0;
		double fx1 = f(x1);
		if (fx1 == 0) {
			return x1;
		}

		if (fa * fx1 < 0) {
			b = x1;
		} else {
			a = x1;
		}

		if (b - a < epsilon) {
			return x1;
		}
	}

	fprintf(stderr, "no solution\n");
	exit(1);
}

double f312(double x)
{
	return log(x) + 2 * x - 6;
}

double f_example2(double x)
{
	return pow(2, x) + 3 * x - 7;
}

double f_practice1(double x)
{
	return x * x * x + 1.1 * x * x + 0.9 * x - 1.4;
}

double f_practice2(double x)
{
	return x + log10(x) - 3;
}

double a3(double x)
{
	return (x + 1) * (x - 2) * (x - 3) - 1;
}

double a4(double x)
{
	return pow(0.8, x) - 1 - log(x);
}

double a5(double x)
{
	return log(x) - 2 / x;
}

double b1(double x)
{
	return 2 * x * x - 3 * x - 1;
}

double b2(double x)
{
	return x * x * x - 6 * x * x - 3 * x + 5;
}

double b3(double x)
{
	return -pow(x, 4) - 6 * pow(x, 3) - 13 * x * x - 12 * x - 2;
}

void print(char* name, Function f, double a, double b, int precision)
{
	double epsilon = pow(0.1, precision);
	char fmt[32];
	sprintf(fmt, "%%.0%dlf\n", precision);
	printf("方程 %s 在区间[%d,%d]内精确到0.", name, (int)a, (int)b);
	for (int i = 1; i < precision; i++) {
		printf("0");
	}
	printf("1的近似解为: ");
	printf(fmt, bisection(f, a, b, epsilon));
}

int main()
{
	print("lnx+2x-6=0", &f312, 2, 3, 2);
	print("2^x+3x=7", &f_example2, 1, 2, 1);
	print("x^3+1.1x^2+0.9x-1.4", &f_practice1, 0, 1, 1);
	print("x=3-lg x", &f_practice2, 2, 3, 2);
	print("(x+1)(x-2)(x-3)=1", &a3, -1, 0, 2);
	print("0.8^x-1=ln x", &a4, 0, 1, 1);
	print("f(x)=ln x-2/x", &a5, 2, 3, 1);
	print("2x^2-3x-1=0", &b1, -1, 0, 2);
	print("2x^2-3x-1=0", &b1, 1, 2, 2);
	print("x^3+5=6x^2+3x", &b2, -2, -1, 1);
	print("x^3+5=6x^2+3x", &b2, 0, 1, 1);
	print("x^3+5=6x^2+3x", &b2, 6, 7, 1);
	print("g(x)=-x^4-6x^3-13x^2-12x-2", &b3, -3, -2, 1);
	print("g(x)=-x^4-6x^3-13x^2-12x-2", &b3, -1, 0, 1);
}