#pragma once

#include "point.h"

namespace math {
namespace analytic_geometry {

// 解高中数学题时一般不会出现无理数坐标、斜率、距离等

// 点斜式方程
// y-y_0 = k(x-x_0)
// 无法表示垂直于x轴的直线，即斜率不为无穷
// 不竖
template <typename T = int>
struct PointSlopeForm {
	Point<T> pt;
	Rational<T> k; // slope
};

// 斜截式方程
// y=kx+b
// 同点斜式，无法表示垂直于x轴的直线，即斜率不为无穷
// 不竖
template <typename T = int>
struct SlopeIntersectForm {
	Rational<T> k; // slope
	Rational<T> b; // intercept
};

// 截距式方程
// x/a+y/b=1
// 无法表示截距为0的直线，即斜率不为0不为无穷
// 不横不竖不过原点
template <typename T = int>
struct IntersectForm {
	Rational<T> a, b;
};

// 两点式方程
// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)
// x1不等x2, y1不等y2
// 无法表示平行于x轴或平行于y轴的直线，即斜率不等0且不为无穷
// 不横不竖
template <typename T = int>
struct TwoPonitForm {
	Point<T> p1, p2;
};

// 一般式方程
// ax+by+c=0
// a,b不同时为0
template <typename T = int>
struct Line {
	Rational<T> a, b, c;

	///////////////////// properties /////////////////////
	
	// slope
	Rational<T> k() const {
		return -b / a;
	}


	///////////////////// converters /////////////////////////

	// 点斜式转为一般式
	// y-y0=k(x-x0)
	// kx-y+y0-kx0 = 0
	Line& fromPointSlopeForm(const PointSlopeForm<T>& line) {
		a = line.k;
		b = -1;
		c = line.pt.y - line.k * line.pt.x;
		simplify();
		return *this;
	}

	// 斜截式转为一般式
	Line& fromSlopeIntersectForm(const SlopeIntersectForm<T>& line) {
		a = line.k;
		b = -1;
		c = line.b;
		simplify();
		return *this;
	}

	// 两点式转为一般式
	Line& fromTwoPointForm(const TwoPonitForm<T>& line) {
		a = (line.p2.y - line.p1.y) / (line.p2.x - line.p1.x);
		b = -1;
		c = line.p1.y - a * line.p1.x;
		simplify();
		return *this;
	}

	// 一般式转为点斜式
	// 斜率必须存在，即b不能为0
	PointSlopeForm<T> toPointSlopeForm() const {
		PointSlopeForm<T> res;
		res.k = -a / b;
		res.pt.x = 0;
		res.pt.y = -c / b;
		return res;
	}

	// 一般式转为斜截式
	// 斜率必须存在，即b不能为0
	SlopeIntersectForm<T> toSlopeIntersectForm() const {
		SlopeIntersectForm<T> res;
		res.k = -a / b;
		res.b = -c / b;
		return res;
	}

	

	///////////////////// relations /////////////////////

	// 平行于
	bool parallelTo(const Line<T>& rhs) const {
		return a * rhs.b - rhs.a * b == 0;
	}

	// 垂直于
	bool verticalTo(const Line<T>& rhs) const {
		return a * rhs.a + b * rhs.b == 0;
	}

	// 点在直线上
	bool ptOnLine(const Point<T>& pt) const {
		return distance(pt) == 0;
	}


	///////////////////// math /////////////////////

	// 以 x 计算 y
	// 要求 b!=0 即 斜率存在
	Rational<T> y(const Rational<T>& x) const {
		return (-a * x - c) / b;
	}

	// x=0, y=?
	Rational<T> y0() const {
		return y(0);
	}

	// 以 y 计算 x
	// 要求 a!=0 即斜率不为0
	Rational<T> x(const Rational<T>& y) const {
		return (-b * y - c) / a;
	}

	// y=0, x=?
	Rational<T> x0() const {
		return x(0);
	}


	///////////////////// point /////////////////////

	// 点到直线距离
	Rational<T> distance(const Point<T>& p) const {
		return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
	}

	// 两点到直线的最小距离和
	Rational<T> minDistance(const Point<T>& a, const Point<T>& b) const {
		if (ptOnLine(a)) {
			return distance(b);
		} else if (ptOnLine(b)) {
			return distance(a);
		} else {
			Point<T> p = symmetricPoint(a);
			return distance(p, b);
		}
	}

	// 点在直线上的投影
	Point<T> projection(const Point<T>& p) const {
		Rational<T> denom = a * a + b * b;
		Rational<T> x = b * b * p.x - a * b * p.y - a * c;
		Rational<T> y = a * a * p.y - a * b * p.x - b * c;
		x /= denom;
		y /= denom;
		return { x, y };
	}

	// 点关于直线的对称点
	Point<T> symmetricPoint(const Point<T>& p) const {
		Rational<T> denom = a * a + b * b;
		Rational<T> x = (b * b - a * a) * p.x - 2 * a * b * p.y - 2 * a * c;
		Rational<T> y = (a * a - b * b) * p.y - 2 * a * b * p.x - 2 * b * c;
		x /= denom;
		y /= denom;
		return { x, y };
	}

	// 关于点的对称直线
	Line symmetricLine(const Point<T>& p) const {
		Line l = *this;
		Rational<T> m = -(a * p.x + b * p.y);
		Rational<T> n = abs(a * p.x + b * p.y + c);
		Rational<T> C = m + n;
		if (C != l.c) {
			l.c = C;
		} else {
			l.c = m - n;
		}
		return l;
	}


	///////////////////// line /////////////////////
	
	// 直线到直线距离
	Rational<T> distance(const Line<T>& rhs) const {
		if (!parallelTo(rhs)) return 0;
		Line<T> l1 = *this, l2 = rhs;
		l1.simplify(); l2.simplify();
		return abs(l1.c - l2.c) / sqrt(l1.a * l1.a + l1.b * l1.b);
	}

	// 与另一直线的交点
	// 调用前确保两直线不平行
	Point<T> intersectionPoint(const Line<T>& rhs) const {
		Rational<T> denom = a * rhs.b - rhs.a * b;
		Rational<T> x = b * rhs.c - rhs.b * c;
		Rational<T> y = rhs.a * c - a * rhs.c;
		x /= denom;
		y /= denom;
		return { x, y };
	}

	// 过一点的垂线
	Line perpendicular(const Point<T>& p) const {
		Line l;
		if (b != 0) { // 斜率存在
			if (a != 0) { // 斜率不为0
				PointSlopeForm<int> vert{ p, b / a };
				l.fromPointSlopeForm(vert);
			} else { // 斜率为0
				l.a = 0;
				l.b = 1;
				l.c = -p.y;
			}
		} else { // 斜率不存在
			l.a = 1;
			l.b = 0;
			l.c = -p.x;
		}
		l.simplify();
		return l;
	}

	// 关于直线L的对称直线
	Line symmetricLine(const Line<T>& L) const {
		if (parallelTo(L)) {
			Point<T> p{ 0, L.y0() };
			return symmetricLine(p);
		} else {
			Point<T> o = intersectionPoint(L);
			Point<T> p{ 0, y0() };
			if (o.x == 0) {
				p.x = 1;
				p.y = y(1);
			}
			Point<T> q = L.symmetricPoint(p);
			TwoPonitForm<T> l2{ o, q };
			Line<T> l3;
			l3.fromTwoPointForm(l2);
			return l3;
		}
	}


	///////////////////// utils /////////////////////

	// 化为abc都为整数且a>=0的形式
	void simplify() {
		Rational<T> A = abs(a);
		Rational<T> B = abs(b);
		Rational<T> C = abs(c);

		T l = lcm(A.q, B.q);
		l = lcm(l, C.q);
		if (l > 1) {
			A.p *= l / A.q;
			B.p *= l / B.q;
			C.p *= l / C.q;
			A.q = B.q = C.q = 1;
		}

		T g = gcd(A.p, B.p);
		g = gcd(g, C.p);
		if (g > 1) {
			A.p /= g;
			B.p /= g;
			C.p /= g;
		}

		a = a.negative() ? -A : A;
		b = b.negative() ? -B : B;
		c = c.negative() ? -C : C;

		if (a.negative()) {
			a.negate();
			b.negate();
			c.negate();
		} else if (a == 0 && b.negative()) {
			b.negate();
			c.negate();
		}
	}

	std::string toString() const {
		std::string s;
		if (a != 0) {
			s += a.toString();
			s += "x";
		}
		if (b != 0) {
			if (b.positive()) {
				s += "+";
			}
			s += b.toString();
			s += "y";
		}
		if (c != 0) {
			if (!s.empty() && c.positive()) {
				s += "+";
			}
			s += c.toString();
		}
		s += "=0";
		return s;
	}
};







}
}
