#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <stdlib.h>
#include "common.h"

namespace math {


// forward declarations
class BigInt;
BigInt abs(const BigInt& i);


class BigInt {
	std::string value;
	char sign;

public:
	/////////////////////// ctors ////////////////////////////
	BigInt() : value("0"), sign('+') {}
	BigInt(long long val) : value(std::to_string(::abs(val))), sign(val < 0 ? '-' : '+') {}
	BigInt(const BigInt& rhs) :value(rhs.value), sign(rhs.sign) {}
	BigInt(const std::string& str) {
		auto r = fromString(str);
		value = r.value;
		sign = r.sign;
	}


	/////////////////////// assignments /////////////////////
	BigInt& operator=(const BigInt& rhs) {
		value = rhs.value;
		sign = rhs.sign;
		return *this;
	}

	BigInt& operator=(long long val) {
		BigInt r(val);
		return *this = r;
	}

	BigInt& operator=(const std::string& str) {
		auto r = fromString(str);
		return *this = r;
	}


	/////////////////////// relations ////////////////////////////////////

	bool operator==(const BigInt& rhs) const {
		return sign == rhs.sign && value == rhs.value;
	}
	bool operator==(long long n) const {
		return (*this) == BigInt(n);
	}
	bool operator==(const std::string& str) const {
		return (*this) == fromString(str);
	}

	bool operator!=(const BigInt& rhs) const {
		return !(*this == rhs);
	}
	bool operator!=(long long n) const {
		return !(*this == BigInt(n));
	}
	bool operator!=(const std::string& str) const {
		return !(*this == fromString(str));
	}

	bool operator<(const BigInt& rhs) const {
		if (sign == rhs.sign) {
			if (sign == '+') {
				return value.size() < rhs.value.size() || (value.size() == rhs.value.size() && value < rhs.value);
			} else {
				return value.size() > rhs.value.size() || (value.size() == rhs.value.size() && value > rhs.value);
			}
		} else {
			return sign == '-';
		}
	}

	bool operator>(const BigInt& rhs) const {
		return (*this != rhs) && !(*this < rhs);
	}

	bool operator<=(const BigInt& rhs) const {
		return (*this < rhs) || (*this == rhs);
	}

	bool operator>=(const BigInt& rhs) const {
		return (*this > rhs) || (*this == rhs);
	}


	/////////////////////// unary operators ////////////////
	
	BigInt operator-() const {
		BigInt r; r.value = value;
		if (value != "0") {
			r.sign = sign == '+' ? '-' : '+';
		}
		return r;
	}

	/////////////////////// binary operators ////////////////

	BigInt operator+(const BigInt& rhs) const {
		// 异号的调用减法，确保两数同号
		if (sign == '+' && rhs.sign == '-') {
			return *this - (-rhs);
		} else if (sign == '-' && rhs.sign == '+') {
			return rhs - (-(*this));
		}

		BigInt res;
		res.value.clear();
		int sum, carry = 0;
		std::string a = value, b = rhs.value;
		while (!a.empty() || !b.empty()) {
			sum = carry;
			if (!a.empty()) {
				sum += a.back() - '0';
				a.pop_back();
			}
			if (!b.empty()) {
				sum += b.back() - '0';
				b.pop_back();
			}
			res.value.insert(res.value.begin(), (sum % 10) + '0');
			carry = sum / 10;
		}

		if (carry) {
			res.value.insert(res.value.begin(), carry + '0');
		}

		if (sign == '-' && res.value != "0") {
			res.sign = '-';
		}

		return res;
	}

	BigInt operator+(long long n) const {
		return (*this) + BigInt(n);
	}

	BigInt operator+(const std::string& str) const {
		return (*this) + fromString(str);
	}

	BigInt operator-(const BigInt& rhs) const {
		// 异号的调用加法，确保两数同号
		if (sign == '+' && rhs.sign == '-') {
			return *this + (-rhs);
		} else if (sign == '-' && rhs.sign == '+') {
			return -(-(*this) + rhs);
		}
		
		BigInt res;
		res.value.clear();
		std::string large, small;
		if (abs(*this) > abs(rhs)) {
			large = value;
			small = rhs.value;
			res.sign = sign == '-' ? '-' : '+';
		} else {
			large = rhs.value;
			small = value;
			res.sign = sign == '+' ? '-' : '+';
		}

		int borrow = 0;
		while (!large.empty()) {
			int a = large.back() - '0'; large.pop_back();
			if (!small.empty()) {
				borrow += small.back() - '0'; small.pop_back();
			}
			if (a >= borrow) {
				res.value.insert(res.value.begin(), a - borrow + '0');
				borrow = 0;
			} else {
				res.value.insert(res.value.begin(), a + 10 - borrow + '0');
				borrow = 1;
			}
		}

		while (res.value.size() > 1 && res.value.front() == '0') {
			res.value = res.value.substr(1);
		}

		if (res.value == "0") {
			res.sign = '+';
		}

		return res;
	}

	BigInt operator-(long long n) const {
		return (*this) - BigInt(n);
	}

	BigInt operator-(const std::string& str) const {
		return (*this) - fromString(str);
	}

	BigInt operator*(const BigInt& rhs) const {
		if (*this == 0 || rhs == 0) {
			return {};
		} else if (*this == 1) {
			return rhs;
		} else if (rhs == 1) {
			return *this;
		}

		BigInt res;

		std::string large, small;
		if (abs(*this) > abs(rhs)) {
			large = value;
			small = rhs.value;
		} else {
			large = rhs.value;
			small = value;
		}

		int k = 0;
		for (auto iter = small.crbegin(); iter != small.crend(); iter++, k++) {
			std::string prod;
			int carry = 0;
			for (auto jter = large.crbegin(); jter != large.crend(); jter++) {
				carry += (*iter - '0') * (*jter - '0');
				prod.insert(prod.begin(), (carry % 10) + '0');
				carry /= 10;
			}
			if (carry) {
				prod.insert(prod.begin(), carry + '0');
			}
			for (int i = 0; i < k; i++) {
				prod.push_back('0');
			}

			res += prod;
		}
		res.sign = sign == rhs.sign ? '+' : '-';

		return res;
	}

	BigInt operator*(long long n) const {
		return (*this) * BigInt(n);
	}

	BigInt operator*(const std::string& str) const {
		return (*this) * fromString(str);
	}

	std::tuple<BigInt, BigInt> divide_mod(const BigInt& rhs) const {
		BigInt quotient, remainder;
		if (rhs == 0) {
			throw std::logic_error("Divide by zero");
			return {};
		} else if (rhs == 1) {
			quotient = *this;
			return std::make_tuple(quotient, remainder);
		} else if (rhs == -1) {
			quotient = -(*this);
			return std::make_tuple(quotient, remainder);
		}

		auto dividend = abs(*this);
		auto divisor = abs(rhs);
		if (dividend < divisor) {
			return std::make_tuple(quotient, dividend);
		}

		while (dividend >= divisor) {
			dividend -= divisor;
			++quotient;
		}
		remainder = dividend;

		if (sign != rhs.sign) {
			quotient.sign = '-';
			remainder.sign = '-';
		}

		if (remainder.value == "0") {
			remainder.sign = '+';
		}

		return std::make_tuple(quotient, remainder);
	}
	std::tuple<BigInt, BigInt> divide_mod(long long n) const {
		return divide_mod(BigInt(n));
	}
	std::tuple<BigInt, BigInt> divide_mod(const std::string& str) const {
		return divide_mod(fromString(str));
	}

	BigInt divide(const BigInt& rhs) const {
		return std::get<0>(divide_mod(rhs));		
	}
	BigInt divide(long long n) const {
		return std::get<0>(divide_mod(n));
	}
	BigInt divide(const std::string& str) const {
		return std::get<0>(divide_mod(str));
	}

	BigInt mod(const BigInt& rhs) const {
		return std::get<1>(divide_mod(rhs));
	}
	BigInt mod(long long n) const {
		return std::get<1>(divide_mod(n));
	}
	BigInt mod(const std::string& str) const {
		return std::get<1>(divide_mod(str));
	}

	BigInt operator/(const BigInt& rhs) const {
		return divide(rhs);
	}
	BigInt operator/(long long n) const {
		return divide(n);
	}
	BigInt operator/(const std::string& str) const {
		return divide(str);
	}

	BigInt operator%(const BigInt& rhs) const {
		return mod(rhs);
	}
	BigInt operator%(long long n) const {
		return mod(n);
	}
	BigInt operator%(const std::string& str) const {
		return mod(str);
	}

	/////////////////////// arithmetic assignments ///////////////////////

	BigInt& operator+=(const BigInt& rhs) {
		auto r = (*this) + rhs;
		return *this = r;
	}
	BigInt& operator+=(long long n) {
		auto r = (*this) + n;
		return *this = r;
	}
	BigInt& operator+=(const std::string& str) {
		auto r = (*this) + str;
		return *this = r;
	}

	BigInt& operator-=(const BigInt& rhs) {
		auto r = (*this) - rhs;
		return *this = r;
	}
	BigInt& operator-=(long long n) {
		auto r = (*this) - n;
		return *this = r;
	}
	BigInt& operator-=(const std::string& str) {
		auto r = (*this) - str;
		return *this = r;
	}

	BigInt& operator*=(const BigInt& rhs) {
		auto r = (*this) * rhs;
		return *this = r;
	}
	BigInt& operator*=(long long n) {
		auto r = (*this) * n;
		return *this = r;
	}
	BigInt& operator*=(const std::string& str) {
		auto r = (*this) * str;
		return *this = r;
	}

	BigInt& operator/=(const BigInt& rhs) {
		auto r = (*this) / rhs;
		return *this = r;
	}
	BigInt& operator/=(long long n) {
		auto r = (*this) / n;
		return *this = r;
	}
	BigInt& operator/=(const std::string& str) {
		auto r = (*this) / str;
		return *this = r;
	}

	BigInt& operator%=(const BigInt& rhs) {
		auto r = (*this) % rhs;
		return *this = r;
	}
	BigInt& operator%=(long long n) {
		auto r = (*this) % n;
		return *this = r;
	}
	BigInt& operator%=(const std::string& str) {
		auto r = (*this) % str;
		return *this = r;
	}

	/////////////////////// inc & dec ////////////////////////////////////

	BigInt& operator++() {
		*this += 1;
		return *this;
	}

	BigInt& operator--() {
		*this -= 1;
		return *this;
	}

	BigInt operator++(int) {
		auto r = *this;
		*this += 1;
		return r;
	}

	BigInt operator--(int) {
		auto r = *this;
		*this -= 1;
		return r;
	}

	/////////////////////// stream ///////////////////////////////////////
	friend std::ostream& operator<<(std::ostream& os, const BigInt& rhs) {
		if (rhs.sign == '-') {
			os << rhs.sign;
		}
		os << rhs.value;
		return os;
	}

	/////////////////////// utils ////////////////////////////////////////

	std::string toString(PMO pmo = PMO::ShowMinus) const {
		std::string s;
		if (pmo == PMO::Show) {
			s.push_back(sign);
		} else if (pmo == PMO::ShowMinus && sign == '-') {
			s.push_back('-');
		}
		s += value;
		return s;
	}

	int toInt() const {
		if (sign == '+') {
			if (*this > BigInt(INT_MAX)) {
				throw std::logic_error("sorry, too big to convert to int");
			}
		} else {
			if (*this < BigInt(INT_MIN)) {
				throw std::logic_error("sorry, too big to convert to int");
			}
		}
		return std::stoi(value);
	}

	long long toLongLong() const {
		if (sign == '+') {
			if (*this > BigInt(LLONG_MAX)) {
				throw std::logic_error("sorry, too big to convert to long long");
			}
		} else {
			if (*this < BigInt(LLONG_MIN)) {
				throw std::logic_error("sorry, too big to convert to long long");
			}
		}
		return std::stoll(value);
	}

	static BigInt fromString(const std::string& str) {
		auto chk = [](const std::string& str) {
			for (const auto& c : str) {
				if (c < '0' || c > '9') {
					return false;
				}
			}
			return true;
		};

		BigInt res;

		if (str.empty()) {
			res.value = "0";
			res.sign = '+';
			return res;
		}

		if (str[0] == '+' || str[0] == '-') {
			std::string num = str.substr(1);
			if (chk(num)) {
				res.value = num;
				res.sign = str[0];
			} else {
				throw std::invalid_argument("Not a valid integer");
			}
		} else {
			if (chk(str)) {
				res.value = str;
				res.sign = '+';
			} else {
				throw std::invalid_argument("Not a valid integer");
			}
		}

		return res;
	}


};


/////////////////////// math ///////////////////////

inline BigInt abs(const BigInt& i) {
	return i < 0 ? (-i) : i;
}

// greatest common divisor
inline BigInt gcd(const BigInt& A, const BigInt& B) {
	auto a = abs(A);
	auto b = abs(B);
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}
	BigInt t;
	if (a < b) {
		t = a;
		a = b;
		b = t;
	}
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

// least common multiple
inline BigInt lcm(const BigInt& a, const BigInt& b) {
	if (a == 0 || b == 0) { return {}; }
	BigInt g = gcd(a, b);
	return math::abs(a * b) / g;
}

// a^b
inline BigInt pow(const BigInt& a, const BigInt& b) {
	if (b < 0) {
		if (a < 0) {
			throw std::logic_error("divide by zero");
			return {};
		}
		return a == 1 ? 1 : 0;
	} else if (b == 0) {
		if (a == 0) {
			throw std::logic_error("0 to the 0");
		}
		return 1;
	}

	BigInt res = a;
	while (b > 1) {
		res *= a;
	}

	return res;
}

inline BigInt sqrt(const BigInt& a) {
	if (a < 0) {
		throw std::logic_error("sqrt of negative");
		return 0;
	}

	if (a >= BigInt(LLONG_MAX)) {
		throw std::invalid_argument("sorry, too big for me");
		return 0;
	}

	long long ll = a.toLongLong();
	return BigInt((long long)::sqrt(ll));
}

//////////////////////////////////////////////////////////

template <>
inline std::string toString(const BigInt& n, PMO pmo) {
	return n.toString(pmo);
}


}
