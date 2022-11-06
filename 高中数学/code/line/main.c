#include <assert.h>



typedef struct Point {
	double x, y;
}Point;

// 点斜式方程
// y-y_0 = k(x-x_0)
// 无法表示垂直于x轴的直线，即斜率不为无穷
// 不竖
typedef struct PointSlopeForm {
	Point pt;
	double k; // slope
}PointSlopeForm;

// 斜截式方程
// y=kx+b
// 同点斜式，无法表示垂直于x轴的直线，即斜率不为无穷
// 不竖
typedef struct SlopeIntersectForm {
	double k; // slope
	double b; // intercept
}SlopeIntersectForm;

// 截距式方程
// x/a+y/b=1
// 无法表示截距为0的直线，即斜率不为0不为无穷
// 不横不竖不过原点
typedef struct IntersectForm {
	double a, b;
}IntersectForm;

// 两点式方程
// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)
// x1不等x2, y1不等y2
// 无法表示平行于x轴或平行于y轴的直线，即斜率不等0且不为无穷
// 不横不竖
typedef struct TwoPonitForm {
	Point p1, p2;
}TwoPonitForm;

// 一般式方程
// ax+by+c=0
// a,b不同时为0
typedef struct GeneralForm {
	double a, b, c;
}GeneralForm;

// 点斜式转为一般式
// y-y0=k(x-x0)
// kx-y+y0-kx0 = 0
GeneralForm generalFromPointSlope(PointSlopeForm line) {
	GeneralForm g;
	g.a = line.k;
	g.b = -1;
	g.c = line.pt.y - line.k * line.pt.x;
	return g;
}

// 一般式转为点斜式
// 斜率必须存在，即b不能为0
PointSlopeForm pointSlopeFromGeneral(GeneralForm line) {
	PointSlopeForm res;
	res.k = -line.a / line.b;
	res.pt.x = 0;
	res.pt.y = -line.c / line.b;
	return res;
}

// 斜截式转为一般式
GeneralForm generalFromSlopeIntersect(SlopeIntersectForm line) {
	GeneralForm g;
	g.a = line.k;
	g.b = -1;
	g.c = line.b;
	return g;
}

// 一般式转为斜截式
// 斜率必须存在，即b不能为0
SlopeIntersectForm slopeIntersectFromGeneral(GeneralForm line) {
	SlopeIntersectForm res;
	res.k = -line.a / line.b;
	res.b = -line.c / line.b;
	return res;
}

// 两点式转为一般式
GeneralForm generalFromTwoPoint(TwoPonitForm line) {
	GeneralForm g;
	g.a = (line.p2.y - line.p1.y) / (line.p2.x - line.p1.x);
	g.b = -1;
	g.c = line.p1.y - g.a * line.p1.x;
	return g;
}

int main()
{

}