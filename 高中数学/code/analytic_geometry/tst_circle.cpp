#include "circle.h"
#include <iostream>

using namespace math;
using namespace analytic_geometry;
using namespace std;

// 圆 (x-3)^2 + (y+1)^2 = 1 关于直线 x+2y-3=0 的对称圆
void p23()
{
	Circle<int> c{ {3, -1}, 1 };
	auto c2 = c.symmetricCircle({ 1,2,-3 });
	cout << c2.toString() << endl;
}







void tst_circle()
{
	p23();
}
