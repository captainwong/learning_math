#pragma once

#include <assert.h>
#include <vector>
#include <string>
#include <functional>


inline int combination(int n, int m) {
	assert(n >= m);
	int c = 1, d = 1;
	int big = m > n - m ? m : n - m;
	int small = m > n - m ? n - m : m;
	for (int i = n; i > big; i--) {
		c *= i;
	}
	for (int i = 2; i <= small; i++) {
		d *= i;
	}
	return c / d;
}

// n 个不同字符中取出 m 个的所有组合
inline std::vector<std::string> combination(const std::vector<std::string>& n, int m) {
	assert(n.size() >= m);

	std::vector<std::string> res;
	std::vector<int> taken;
	std::function<void(const std::vector<std::string>& in, std::vector<std::string>& out, std::vector<int>& taken, int begin, int n)> take;

	auto is_taken = [](const std::vector<int>& taken, int i) {
		for (const auto& j : taken) {
			if (j == i) {
				return true;
			}
		}
		return false;
	};

	take = [&take, &is_taken](const std::vector<std::string>& in, std::vector<std::string>& out, std::vector<int>& taken, int begin, int n) {
		auto origin_taken = taken;
		for (int i = begin; i < in.size(); i++) {
			if (is_taken(taken, i)) continue;
			taken.push_back(i);
			if (n > 1) {
				take(in, out, taken, i + 1, n - 1);
			} else {
				std::string str;
				for (const auto& j : taken) {
					str += (in[j]);
				}
				out.push_back(str);
			}
			taken = origin_taken;
		}
	};

	take(n, res, taken, 0, m);
	return res;
}