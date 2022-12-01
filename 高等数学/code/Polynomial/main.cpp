#include "polynomial.h"
#include <stdio.h>


// Í¬¼ÃÆß°æp143, 1
void test_1()
{

}

// p143, 2
void test_2()
{
	Polynomial polynomial;
	polynomial.append(1, 2);
	polynomial.append(-3, 1);
	polynomial.append(1, 0);

	printf("%s\n", polynomial.toString2().c_str());

	polynomial = polynomial.power(3);
	printf("%s\n", polynomial.toString2().c_str());

	Polynomial maclaurin = polynomial.maclaurinExpansion();
	printf("%s\n", maclaurin.toString2().c_str());

	/*Polynomial res, der = polynomial;
	for (int exp = 0; !der.empty(); exp++) {
		res.append(der.value(0), exp, false);
		der = der.derivative();
	}*/
}

int main()
{
	test_2();
}
