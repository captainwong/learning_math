#include "rational.h"
#include "bigint.h"
#include "bigrational.h"
#include <assert.h>

// https://pintia.cn/problem-sets/14/exam/problems/815
/*
7-35 有理数均值
分数 20
作者 乔林
单位 清华大学
本题要求编写程序，计算N个有理数的平均值。

输入格式：
输入第一行给出正整数N（≤100）；第二行中按照a1/b1 a2/b2 …的格式给出N个分数形式的有理数，其中分子和分母全是整形范围内的整数；如果是负数，则负号一定出现在最前面。

输出格式：
在一行中按照a/b的格式输出N个有理数的平均值。注意必须是该有理数的最简分数形式，若分母为1，则只输出分子。

输入样例1：
4
1/2 1/6 3/6 -5/10
输出样例1：
1/6
输入样例2：
2
4/3 2/3
输出样例2：
1
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
*/

#if 0

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    if (a < b) {
        int t = a;
        a = b;
        b = t;
    }

    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int lcm(int a, int b)
{
    long long g = gcd(a, b);
    return (long long)a / g * b;
}

void simp(int* pa, int* pb)
{
    int g = gcd(*pa, *pb);
    *pa /= g;
    *pb /= g;
}

typedef struct Rational {
    int numer;
    int denom;
}Rational;


void read(Rational* r)
{
    scanf("%d/%d", &r->numer, &r->denom);
    simp(&r->numer, &r->denom);
    if (r->denom < 0) {
        r->numer = -r->numer;
        r->denom = -r->denom;
    }
}

void add(Rational* r1, Rational* r2)
{
    int denom = lcm(r1->denom, r2->denom);
    int numer = r1->numer * (denom / r1->denom) + r2->numer * (denom / r2->denom);
    simp(&numer, &denom);
    r1->numer = numer;
    r1->denom = denom;
}

int main()
{
    int N;
    scanf("%d", &N);
    Rational* rs = malloc(N * sizeof(Rational));
    for (int i = 0; i < N; i++) {
        read(&rs[i]);
    }

    Rational r = { 0, 1 };
    for (int i = 0; i < N; i++) {
        add(&r, &rs[i]);
    }
    if (r.numer % N == 0) {
        r.numer /= N;
    } else {
        r.denom *= N;
    }
    simp(&r.numer, &r.denom);
    if (r.denom == 1) {
        printf("%d", r.numer);
    } else {
        printf("%d/%d", r.numer, r.denom);
    }
}

#endif

using namespace math;

Rational<BigInt> read()
{
    int p, q;
    scanf("%d/%d", &p, &q);
    return Rational<BigInt>(p, q);
}

// PTA提交测试通过
void pta()
{
    int N;
    scanf("%d", &N);
    Rational<BigInt> sum;
    for (int i = 0; i < N; i++) {
        sum += read();
    }
    sum /= BigInt(N);
    printf("%s\n", sum.toString().c_str());
}

void tst_rational()
{
    /*
    4
    1/2 1/6 3/6 -5/10

    */
    Rational<BigInt> sum;
    sum += Rational<BigInt>(1, 2);
    sum += Rational<BigInt>(1, 6);
    sum += Rational<BigInt>(3, 6);
    sum += Rational<BigInt>(-5, 10);
    sum /= BigInt(4);
    assert(sum == Rational<BigInt>(1, 6));
    //printf("%s\n", sum.toString().c_str());
    //

    Rational<int> i(333);
    i.toString();
}
