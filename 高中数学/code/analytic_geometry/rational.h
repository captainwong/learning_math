#pragma once

#include <string>

namespace math {

// greatest common divisor
template <typename T = int>
T gcd(T a, T b) {
    while (b) {
        T t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// least common multiple
template <typename T = int>
T lcm(T a, T b) {
    T g = gcd(a, b);
    return a / g * b;
}

// ÓÐÀíÊý p/q, q!= 0
template <typename T = int>
struct Rational {
    T p; // numerator
    T q; // denominator

    Rational() : p(0), q(1) {}

    Rational(T a) : p(a), q(1) {}

    Rational(T a, T b) {
        if (b == 0) {
            p = 0; q = 1;
        } else {
            p = a;
            q = b;
            simplify();
        }
    }

    void make_sure_q_is_positive() {
        if (q < 0) {
            p = -p;
            q = -q;
        }
    }

    void simplify() {
        T g = gcd(p, q);
        p /= g;
        q /= g;
        make_sure_q_is_positive();
    }

    Rational add(const Rational& rhs) const {
        Rational r;
        r.q = lcm(q, rhs.q);
        r.p = p * (r.q / q) + rhs.p * (r.q / rhs.q);
        r.simplify();
        return r;
    }

    Rational operator+(const Rational& rhs) const {
        return add(rhs);
    }

    Rational& operator+=(const Rational& rhs) {
        Rational r = add(rhs);
        return *this = r;
    }

    Rational sub(const Rational& rhs) const {
        Rational r = rhs; r.p = -r.p;
        return add(r);
    }

    Rational operator-(const Rational& rhs) const {
        return sub(rhs);
    }

    Rational& operator-=(const Rational& rhs) {
        Rational r = sub(rhs);
        return *this = r;
    }

    Rational multiply(const Rational& rhs) const {
        Rational r;
        r.p = p * rhs.p;
        r.q = q * rhs.q;
        r.simplify();
        return r;
    }

    Rational operator*(const Rational& rhs) const {
        return multiply(rhs);
    }

    Rational operator*=(const Rational& rhs) {
        auto r = multiply(rhs);
        return *this = r;
    }

    Rational divide(const Rational& rhs) const {
        Rational r;
        r.p = p * rhs.q;
        r.q = q * rhs.p;
        r.simplify();
        return r;
    }

    Rational operator/(const Rational& rhs) const {
        return divide(rhs);
    }

    Rational operator/=(const Rational& rhs) {
        auto r = divide(rhs);
        return *this = r;
    }

    bool operator==(const Rational& rhs) const {
        return p == rhs.p && q == rhs.q;
    }

    std::string toString(char c_div = '/') const {
        std::string s;
        if (p < 0) {
            s.push_back('-');
        }
        s += std::to_string(p);
        if (q != 1) {
            s.push_back(c_div);
            s += std::to_string(q);
        }
        return s;
    }
};

}
