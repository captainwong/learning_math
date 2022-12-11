#pragma once

#include "rational.h"

namespace math {

// 带系数、底数、指数的有理数扩展
// 可以表示有理数和简单的无理数 如 2\sqrt {3}, 3*2^{1/2}
template <typename T = int>
struct RationalEx {
	Rational<T> coefficient;
	Rational<T> base;
	Rational<T> exponent;


};





}
