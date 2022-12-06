#include "bigint.h"
#include <assert.h>

void tst_bigint()
{
	using namespace math;

	BigInt a; 
	
	assert(a == 0);
	assert(a == "0");

	a = "-3";
	assert(a == -3);

	a = "123456789";
	assert(a == 123456789);
	a = "-123456789";
	assert(a == -123456789);

	a = 321;
	a -= "21";
	assert(a == "300");

	a += -300;
	assert(a == "0");

	a -= 123;
	assert(a == -123);

	a *= 2;
	assert(a == -246);

	a *= -1;
	assert(a == 246);

	a = 123;
	a *= -23;
	assert(a == -2829);

	BigInt quotient, remainder;
	std::tie(quotient, remainder) = a.divide_mod(123);
	assert(quotient == -23);
	assert(remainder == 0);


}
