#pragma once

#include <string>
#include <math.h>

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

//template <typename T>
//inline T abs(T&& t) {
//	return ::abs(std::forward<T>(t));
//}


// plus minus option
enum class PMO {
    ShowMinus, // 只显示负号
    Show, // 不论正负号都显示
    Hide, // 总是隐藏
};

template <typename T>
inline std::string toString(const T& t, PMO pmo = PMO::ShowMinus) {
    std::string s;
    if (pmo == PMO::Show) {
        s.push_back(t < 0 ? '-' : '+');
    } else if (pmo == PMO::ShowMinus && t < 0) {
        s.push_back('-');
    }
	return std::to_string(abs(t));
}


}
