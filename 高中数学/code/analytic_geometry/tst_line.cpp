#include "line.h"
#include <assert.h>

using namespace math;
using namespace analytic_geometry;
using namespace line;

// �����֡�������ѧ100����
// ֱ��

// ���� (1,2) ��ֱ�� x+2y+1=0 �ϵ�ͶӰ
void p25()
{
	Line<int> l{ 1, 2, 1 };
	Point<int> p{ 1,2 };

	auto p2 = l.projection(p);
	Point<int> p3{ Rational<int>(-1, 5), Rational<int>(-2, 5) };
	assert(p2 == p3);
}

// 

void tst_line()
{
	p25();
}
