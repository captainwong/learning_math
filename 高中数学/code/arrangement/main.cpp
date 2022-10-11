#include "arrangement.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>

// 人教A版高中数学选修2-3，page20
void p1()
{
	auto res = arrangement({ 'a', 'b', 'c', 'd', }, 2);
	std::cout << res.size() << std::endl;
	for (const auto& str : res) {
		std::cout << str << std::endl;
	}
}

void p2()
{
	auto res = arrangement({ 'a', 'b', 'c', 'd', 'e' }, 2);
	std::cout << res.size() << std::endl;
	for (const auto& str : res) {
		std::cout << str << std::endl;
	}
}

void p3()
{
	printf("%d\n", arrangement(15, 4));
	printf("%d\n", arrangement(7, 7));
	printf("%d\n", arrangement(8, 4) - 2 * arrangement(8, 2));
	printf("%d\n", arrangement(12, 8) / arrangement(12, 7));
}

int main()
{
	assert(arrangement(10, 4) == 5040);
	assert(arrangement(18, 5) == 1028160);
	assert(arrangement(10, 4) == 5040);
	assert(arrangement(1, 1) == 1);
	assert(arrangement(1, 0) == 1);
	assert(arrangement(0, 0) == 1);

	p1();
	p2();
	p3();
}