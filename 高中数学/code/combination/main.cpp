#include "combination.h"
#include "../arrangement/arrangement.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>

// 人教A版高中数学选修2-3，page25

void p1()
{
	// (1)
	auto res = combination({ "甲", "乙", "丙", "丁"}, 2);
	std::cout << res.size() << std::endl;
	for (const auto& str : res) {
		std::cout << str << std::endl;
	}

	// (2)
	res = arrangement({ "甲", "乙", "丙", "丁" }, 2);
	std::cout << res.size() << std::endl;
	for (const auto& str : res) {
		std::cout << str << std::endl;
	}
}

void p2()
{
	auto res = combination({ "A", "B", "C", "D" }, 3);
	std::cout << res.size() << std::endl;
	for (const auto& str : res) {
		std::cout << str << std::endl;
	}
}

void p5()
{
	printf("%d\n", combination(6, 2));
	printf("%d\n", combination(8, 3));
	printf("%d\n", combination(7, 3) - combination(6, 2));
	printf("%d\n", 3 * combination(8, 3) - 2 * combination(5, 2));
}

// page27 习题1.2

void a1()
{
	printf("%d\n", 5 * arrangement(5, 3) + 4 * arrangement(4, 2));
	printf("%d\n", arrangement(4, 1) + arrangement(4, 2) + arrangement(4, 3) + arrangement(4, 4));
}

void a2()
{
	printf("%d\n", combination(15, 3));
	printf("%d\n", combination(200, 197));
	printf("%lf\n", 1.0 * combination(6, 3) / combination(8, 4));
}

int main()
{
	assert(combination(1, 0) == 1);
	assert(combination(1, 1) == 1);
	assert(combination(0, 0) == 1);
	assert(combination(0, 0) == 1);
	assert(combination(3, 2) == 3);
	assert(combination(4, 3) == 4);
	assert(combination(10, 7) == 120);
	assert(combination(17, 11) == 12376);

	//p1();
	//p2();
	//p5();

	a1();
	a2();
}