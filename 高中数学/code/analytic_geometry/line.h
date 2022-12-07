#pragma once

#include "point.h"

namespace math {
namespace analytic_geometry {
namespace line {


// �������ѧ��ʱһ�㲻��������������ꡢб�ʡ������

// ��бʽ����
// y-y_0 = k(x-x_0)
// �޷���ʾ��ֱ��x���ֱ�ߣ���б�ʲ�Ϊ����
// ����
template <typename T>
struct PointSlopeForm {
	Point<T> pt;
	Rational<T> k; // slope
};

// б��ʽ����
// y=kx+b
// ͬ��бʽ���޷���ʾ��ֱ��x���ֱ�ߣ���б�ʲ�Ϊ����
// ����
template <typename T>
struct SlopeIntersectForm {
	Rational<T> k; // slope
	Rational<T> b; // intercept
};

// �ؾ�ʽ����
// x/a+y/b=1
// �޷���ʾ�ؾ�Ϊ0��ֱ�ߣ���б�ʲ�Ϊ0��Ϊ����
// ���᲻������ԭ��
template <typename T>
struct IntersectForm {
	Rational<T> a, b;
};

// ����ʽ����
// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)
// x1����x2, y1����y2
// �޷���ʾƽ����x���ƽ����y���ֱ�ߣ���б�ʲ���0�Ҳ�Ϊ����
// ���᲻��
template <typename T>
struct TwoPonitForm {
	Point<T> p1, p2;
};

// һ��ʽ����
// ax+by+c=0
// a,b��ͬʱΪ0
template <typename T>
struct Line {
	Rational<T> a, b, c;

	///////////////////// properties /////////////////////
	
	// slope
	Rational<T> k() const {
		return -b / a;
	}


	///////////////////// converters /////////////////////////

	// ��бʽתΪһ��ʽ
	// y-y0=k(x-x0)
	// kx-y+y0-kx0 = 0
	Line& fromPointSlopeForm(const PointSlopeForm<T>& line) {
		a = line.k;
		b = -1;
		c = line.pt.y - line.k * line.pt.x;
		simplify();
		return *this;
	}

	// б��ʽתΪһ��ʽ
	Line& fromSlopeIntersectForm(const SlopeIntersectForm<T>& line) {
		a = line.k;
		b = -1;
		c = line.b;
		simplify();
		return *this;
	}

	// ����ʽתΪһ��ʽ
	Line& fromTwoPointForm(const TwoPonitForm<T>& line) {
		a = (line.p2.y - line.p1.y) / (line.p2.x - line.p1.x);
		b = -1;
		c = line.p1.y - a * line.p1.x;
		simplify();
		return *this;
	}

	// һ��ʽתΪ��бʽ
	// б�ʱ�����ڣ���b����Ϊ0
	PointSlopeForm<T> toPointSlopeForm() const {
		PointSlopeForm<T> res;
		res.k = -a / b;
		res.pt.x = 0;
		res.pt.y = -c / b;
		return res;
	}

	// һ��ʽתΪб��ʽ
	// б�ʱ�����ڣ���b����Ϊ0
	SlopeIntersectForm<T> toSlopeIntersectForm() const {
		SlopeIntersectForm<T> res;
		res.k = -a / b;
		res.b = -c / b;
		return res;
	}

	

	///////////////////// relations /////////////////////

	// ƽ����
	bool parallelTo(const Line<T>& rhs) const {
		return a * rhs.b - rhs.a * b == 0;
	}

	// ��ֱ��
	bool verticalTo(const Line<T>& rhs) const {
		return a * rhs.a + b * rhs.b == 0;
	}

	// ����ֱ����
	bool ptOnLine(const Point<T>& pt) const {
		return distance(pt) == 0;
	}

	///////////////////// math /////////////////////

	// �㵽ֱ�߾���
	Rational<T> distance(const Point<T>& p) const {
		return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
	}

	// ֱ�ߵ�ֱ�߾���
	Rational<T> distance(const Line<T>& rhs) const {
		if (!parallelTo(rhs)) return 0;
		Line<T> l1 = *this, l2 = rhs;
		l1.simplify(); l2.simplify();
		return abs(l1.c - l2.c) / sqrt(l1.a * l1.a + l1.b * l1.b);
	}

	// ����ֱ���ϵ�ͶӰ
	Point<T> projection(const Point<T>& pt) const {
		Rational<T> denom = a * a + b * b;
		Rational<T> x = b * b * pt.x - a * b * pt.y - a * c;
		Rational<T> y = a * a * pt.y - a * b * pt.x - b * c;
		x /= denom;
		y /= denom;
		return { x, y };
	}


	///////////////////// utils /////////////////////

	// ��Ϊ�޷�����ʽ
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

		a = A;
		b = B;
		c = C;

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
}
