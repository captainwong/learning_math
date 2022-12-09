#pragma once

#include "rational.h"

namespace math {
namespace analytic_geometry {

// 解高中数学题时一般不会出现无理数坐标

template <typename T = int>
struct Point {
	Rational<T> x, y;

	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator!=(const Point& rhs) const {
		return !(*this == rhs);
	}
};

// 两点距离
template <typename T = int>
Rational<T> distance(const Point<T>& a, const Point<T>& b) {
	return (b.x - a.x) * (b.x - a.x) * (b.y - a.y) * (b.y - a.y);
}

// 两点中点坐标
template <typename T = int>
Point<T> middle(const Point<T>& a, const Point<T>& b) {
	return { (a.x + b.x) / 2, (a.y + b.y) / 2 };
}

// 三点共线
template <typename T = int>
bool threePointsCollinear(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
	return a.x * b.y + b.x * c.y + c.x * a.y == a.x * c.y + b.x * a.y + c.x * b.y;
}


}
}
