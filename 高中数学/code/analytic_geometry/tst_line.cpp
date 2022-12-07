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

// 

void tst_line()
{
	p25();
}
