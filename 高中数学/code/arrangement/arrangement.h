#pragma once

#include <assert.h>
#include <vector>
#include <string>
#include <functional>

inline int factorial(int n) {
	int f = 1;
	for (int i = 2; i <= n; i++) {
		f *= i;
	}
	return f;
}

// 排列数 A_m^n, m <= n
inline int arrangement(int n, int m) {
	assert(n >= m);
	int a = 1;
	for (m = n - m; n > m; n--) {
		a *= n;
	}
	return a;
}

// n 个不同字符中取出 m 个的所有排列
inline std::vector<std::string> arrangement(const std::vector<char>& n, int m) {
	assert(n.size() >= m);

	std::vector<std::string> res;
	std::vector<int> taken;
	std::function<void(const std::vector<char>& in, std::vector<std::string>& out, std::vector<int>& taken, int n)> take;

	auto is_taken = [](const std::vector<int>& taken, int i) {
		for (const auto& j : taken) {
			if (j == i) {
				return true;
			}
		}
		return false;
	};

	take = [&take, &is_taken](const std::vector<char>& in, std::vector<std::string>& out, std::vector<int>& taken, int n) {
		auto origin_taken = taken;
		for (int i = 0; i < in.size(); i++) {
			if (is_taken(taken, i)) continue;
			taken.push_back(i);
			if (n > 1) {
				take(in, out, taken, n - 1);
			} else {
				std::string str;
				for (const auto& j : taken) {
					str.push_back(in[j]);
				}
				out.push_back(str);
			}
			taken = origin_taken;
		}
	};

	take(n, res, taken, m);
	return res;
}
