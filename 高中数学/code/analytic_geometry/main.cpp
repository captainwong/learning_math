#include "rational.h"
#include "bigint.h"

#ifdef _DEBUG
void tst_bigint();
void tst_rational();
#endif

using namespace math;

int main()
{
#ifdef _DEBUG
	tst_bigint();
	tst_rational();
#endif


	Rational<BigInt> a;
}