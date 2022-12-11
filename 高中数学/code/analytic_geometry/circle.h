#pragma once

#include "line.h"

namespace math {
namespace analytic_geometry {


template <typename T = int>
struct Circle {
	Point<T> center;
	Rational<T> ratio;

	Circle() :center(), ratio() {}
	Circle(const Point<T>& p, const Rational<T>& r) : center(p), ratio(abs(r)) {}
	Circle(const Rational<T>& x, const Rational<T>& y, const Rational<T>& r) :center(x, y), ratio(abs(r)) {}

	// 关于直线的对称圆
	Circle symmetricCircle(const Line<T>& l) const {
		Point<T> p = l.symmetricPoint(center);
		return { p, ratio };
	}


	enum class EquationType {
		StandardEquation,
		GeneralEquation,
		ParameterEquation,
	};

	std::string toString(EquationType type = EquationType::StandardEquation) const {
		std::string s;
		switch (type) {
		case EquationType::StandardEquation:
		{
			if (center.x != 0) {
				s = "(x";
				s += (-center.x).toString(PMO::Show);
				s += ")^2+";
			} else {
				s = "x^2+";
			}

			if (center.y != 0) {
				s += "(y";
				s += (-center.y).toString(PMO::Show);
				s += ")^2=";
			} else {
				s += "y^2=";
			}
			s += (ratio * ratio).toString();
			break;
		}
		case EquationType::GeneralEquation:
		{
			s += "x^2+y^2";
			Rational<T> d = -2 * center.x;
			Rational<T> e = -2 * center.y;
			Rational<T> f = (d * d + e * e - 4 * ratio) / 4;
			if (d != 0) {
				s += d.toString(PMO::Show); s += "x";
			}
			if (e != 0) {
				s += e.toString(PMO::Show); s += "y";
			}
			if (f != 0) {
				s += f.toString(PMO::Show);
			}
			s += "=0";
			break;
		}
		case EquationType::ParameterEquation:
		{
			// THETA?
			break;
		}
		}

		return s;
	}
};

}
}
