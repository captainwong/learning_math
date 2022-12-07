#include "rational.h"
#include "bigint.h"

#ifdef _DEBUG
void tst_bigint();
void tst_rational(); 
void tst_line();
#endif

using namespace math;

int main()
{
#ifdef _DEBUG
	tst_bigint();
	tst_rational();
	tst_line();
#endif


	Rational<BigInt> a;
}