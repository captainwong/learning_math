#include <assert.h>



typedef struct Point {
	double x, y;
}Point;

// ��бʽ����
// y-y_0 = k(x-x_0)
// �޷���ʾ��ֱ��x���ֱ�ߣ���б�ʲ�Ϊ����
// ����
typedef struct PointSlopeForm {
	Point pt;
	double k; // slope
}PointSlopeForm;

// б��ʽ����
// y=kx+b
// ͬ��бʽ���޷���ʾ��ֱ��x���ֱ�ߣ���б�ʲ�Ϊ����
// ����
typedef struct SlopeIntersectForm {
	double k; // slope
	double b; // intercept
}SlopeIntersectForm;

// �ؾ�ʽ����
// x/a+y/b=1
// �޷���ʾ�ؾ�Ϊ0��ֱ�ߣ���б�ʲ�Ϊ0��Ϊ����
// ���᲻������ԭ��
typedef struct IntersectForm {
	double a, b;
}IntersectForm;

// ����ʽ����
// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)
// x1����x2, y1����y2
// �޷���ʾƽ����x���ƽ����y���ֱ�ߣ���б�ʲ���0�Ҳ�Ϊ����
// ���᲻��
typedef struct TwoPonitForm {
	Point p1, p2;
}TwoPonitForm;

// һ��ʽ����
// ax+by+c=0
// a,b��ͬʱΪ0
typedef struct GeneralForm {
	double a, b, c;
}GeneralForm;

// ��бʽתΪһ��ʽ
// y-y0=k(x-x0)
// kx-y+y0-kx0 = 0
GeneralForm generalFromPointSlope(PointSlopeForm line) {
	GeneralForm g;
	g.a = line.k;
	g.b = -1;
	g.c = line.pt.y - line.k * line.pt.x;
	return g;
}

// һ��ʽתΪ��бʽ
// б�ʱ�����ڣ���b����Ϊ0
PointSlopeForm pointSlopeFromGeneral(GeneralForm line) {
	PointSlopeForm res;
	res.k = -line.a / line.b;
	res.pt.x = 0;
	res.pt.y = -line.c / line.b;
	return res;
}

// б��ʽתΪһ��ʽ
GeneralForm generalFromSlopeIntersect(SlopeIntersectForm line) {
	GeneralForm g;
	g.a = line.k;
	g.b = -1;
	g.c = line.b;
	return g;
}

// һ��ʽתΪб��ʽ
// б�ʱ�����ڣ���b����Ϊ0
SlopeIntersectForm slopeIntersectFromGeneral(GeneralForm line) {
	SlopeIntersectForm res;
	res.k = -line.a / line.b;
	res.b = -line.c / line.b;
	return res;
}

// ����ʽתΪһ��ʽ
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