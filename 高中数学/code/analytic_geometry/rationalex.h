#pragma once

#include "rational.h"

namespace math {

// ��ϵ����������ָ������������չ
// ���Ա�ʾ�������ͼ򵥵������� �� 2\sqrt {3}, 3*2^{1/2}
template <typename T = int>
struct RationalEx {
	Rational<T> coefficient;
	Rational<T> base;
	Rational<T> exponent;


};





}
