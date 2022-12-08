#ifdef _DEBUG

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

// ԭ����ֱ���ϵ���Ӱ��Ϊ (-2,1)��ֱ��Ϊ
void p26()
{
	Point<int> o{ 0,0 };
	Point<int> p{ -2,1 };
	Line<int> l;
	l.fromTwoPointForm(TwoPonitForm<int>{ o, p });
	auto l2 = l.perpendicular(p);
	assert(l2.a == 2 && l2.b == -1 && l2.c == 5);
}

// �� (1,2) ���� x+2y+1=0 �ĶԳƵ�
void p27()
{
	Line<int> l{ 1,2,1 };
	auto p = l.symmetricPoint(Point<int>{1, 2});
	Point<int> p2{ Rational<int>(-7, 5), Rational<int>(-14, 5) };
	assert(p == p2);
}

// �� (-4,4) ���� 3x+y-2=0 �ĶԳƵ�
void p28()
{
	Line<int> l{ 3,1,-2 };
	auto p = l.symmetricPoint(Point<int>{-4, 4});
	Point<int> p2{ 2, 6 };
	assert(p == p2);
}

// �� 3x+y-2=0 ���� (-4,4) �ĶԳ�ֱ��
void p29()
{
	Line<int> l{ 3,1,-2 };
	auto l2 = l.symmetricLine(Point<int>{-4, 4});
	assert(l2.a == 3 && l2.b == 1 && l2.c == 18);
}

// �� x-2y-1=0 ���䵽 x+2y+3=0 �ķ���ֱ��
void p30()
{
	Line<int> l1{ 1,2,3 };
	Line<int> l2{ 1,-2,-1 };
	auto l3 = l2.symmetricLine(l1);
	assert(l3.a == 11 && l3.b == 2 && l3.c == 13);
}

// �� x-2y+1=0 ���� x=1 �ĶԳ�ֱ��
void p31()
{
	Line<int> l2{ 1,-2,1 };
	Line<int> l1{ 1,0,-1 };
	auto l3 = l2.symmetricLine(l1);
	assert(l3.a == 1 && l3.b == 2 && l3.c == -3);
}

// ��(-1,4) �����Ĺ��ߣ����� 2x+3y-6=0 ����󾭹� (3, 62/13)���������
void p32()
{
	Line<int> l1{ 2,3,-6 };
	Point<int> A = l1.symmetricPoint(Point<int>{-1, 4});
	Point<int> B{ 3, Rational<int>{62, 13} };
	Line<int> l2;
	l2.fromTwoPointForm(TwoPonitForm<int>{A, B});
	assert(l2.a == 13 && l2.b == -26 && l2.c == 85);
}

void tst_line()
{
	p25();
	p26();
	p27();
	p28();
	p29();
	p30();
	p31();
	p32();
}


#endif
