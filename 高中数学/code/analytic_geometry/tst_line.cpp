#ifdef _DEBUG

#include "line.h"
#include <assert.h>

using namespace math;
using namespace analytic_geometry;
using namespace line;

// 李永乐《高三数学100讲》
// 直线

// 计算 (1,2) 在直线 x+2y+1=0 上的投影
void p25()
{
	Line<int> l{ 1, 2, 1 };
	Point<int> p{ 1,2 };

	auto p2 = l.projection(p);
	Point<int> p3{ Rational<int>(-1, 5), Rational<int>(-2, 5) };
	assert(p2 == p3);
}

// 原点在直线上的射影点为 (-2,1)，直线为
void p26()
{
	Point<int> o{ 0,0 };
	Point<int> p{ -2,1 };
	Line<int> l;
	l.fromTwoPointForm(TwoPonitForm<int>{ o, p });
	auto l2 = l.perpendicular(p);
	assert(l2.a == 2 && l2.b == -1 && l2.c == 5);
}

// 求 (1,2) 关于 x+2y+1=0 的对称点
void p27()
{
	Line<int> l{ 1,2,1 };
	auto p = l.symmetricPoint(Point<int>{1, 2});
	Point<int> p2{ Rational<int>(-7, 5), Rational<int>(-14, 5) };
	assert(p == p2);
}

// 求 (-4,4) 关于 3x+y-2=0 的对称点
void p28()
{
	Line<int> l{ 3,1,-2 };
	auto p = l.symmetricPoint(Point<int>{-4, 4});
	Point<int> p2{ 2, 6 };
	assert(p == p2);
}

// 求 3x+y-2=0 关于 (-4,4) 的对称直线
void p29()
{
	Line<int> l{ 3,1,-2 };
	auto l2 = l.symmetricLine(Point<int>{-4, 4});
	assert(l2.a == 3 && l2.b == 1 && l2.c == 18);
}

void tst_line()
{
	p25();
	p26();
	p27();
	p28();
	p29();
}


#endif
