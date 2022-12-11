#include "circle.h"
#include <iostream>

using namespace math;
using namespace analytic_geometry;
using namespace std;

// Բ (x-3)^2 + (y+1)^2 = 1 ����ֱ�� x+2y-3=0 �ĶԳ�Բ
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
