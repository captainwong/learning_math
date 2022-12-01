#include "polynomial.h"


void Polynomial::append(Item item, bool force) {
    if (item.coefficient == 0 && !force) {
        return;
    }

    if (items.empty()) {
        items.push_back(std::make_shared<Item>(item));
        return;
    } else if (items.size() == 1 && items.front()->coefficient == 0) {
        items.front()->coefficient = item.coefficient;
        items.front()->exponent = item.exponent;
        return;
    }

    auto iter = items.begin();
    while (iter != items.end()) {
        if ((*iter)->exponent == item.exponent) {
            (*iter)->coefficient += item.coefficient;
            if ((*iter)->coefficient == 0) {
                items.erase(iter);
            }
            return;
        } else if ((*iter)->exponent < item.exponent) {
            items.insert(iter, std::make_shared<Item>(item));
            return;
        } else {
            iter++;
        }
    }
    items.push_back(std::make_shared<Item>(item));
}

void Polynomial::simplify() {
    do {
        if (items.empty()) {
            break;
        }
        sort();
        auto iter = items.begin();
        while (iter != items.end() && (*iter)->coefficient == 0) {
            iter = items.erase(iter);
        }
        if (iter == items.end()) {
            break;
        }
        auto prev = *iter++;
        while (iter != items.end()) {
            if ((*iter)->coefficient == 0) {
                iter = items.erase(iter);
            } else if (prev->exponent == (*iter)->exponent) {
                prev->coefficient += (*iter)->coefficient;
                iter = items.erase(iter);
            } else {
                prev = *iter++;
            }
        }

        iter = items.begin();
        while (iter != items.end()) {
            if ((*iter)->coefficient == 0) {
                iter = items.erase(iter);
            } else {
                iter++;
            }
        }

    } while (0);

    justify();
}

// 化繁，使得从最高次幂到最低次幂，每项都有元素（以系数为0的元素填充）
void Polynomial::complicate() {
    simplify();
    auto front = items.front();
    auto back = items.back();
    for (int i = 0; i < front->exponent; i++) {
        if (i != back->coefficient) {
            append(Item{ 0, i }, true);
        }
    }
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    Polynomial c;
    for (const auto& item : items) {
        c.append(*item);
    }
    for (const auto& item : rhs.items) {
        c.append(*item);
    }
    c.simplify();
    return c;
}

Polynomial Polynomial::operator+=(const Polynomial& rhs)
{
    auto res = this->operator+(rhs);
    items = res.items;
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const {
    Polynomial c;
    for (const auto& item : items) {
        c.append(*item);
    }
    for (const auto& item : rhs.items) {
        c.append(Item{ -item->coefficient, item->exponent });
    }
    c.simplify();
    return c;
}

Polynomial Polynomial::operator-=(const Polynomial& rhs)
{
    auto res = this->operator-(rhs);
    items = res.items;
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const {
    Polynomial c;
    for (const auto& i : items) {
        for (const auto& j : rhs.items) {
            c.append(*i * *j);
        }
    }
    c.simplify();
    return c;
}

Polynomial Polynomial::operator*=(const Polynomial& rhs)
{
    auto res = this->operator*(rhs);
    items = res.items;
    return *this;
}

Polynomial Polynomial::operator*(const Item& rhs) const {
    Polynomial c;
    for (const auto& i : items) {
        c.append(*i * rhs);
    }
    c.simplify();
    return c;
}

Polynomial Polynomial::operator*=(const Item& rhs)
{
    auto res = this->operator*(rhs);
    items = res.items;
    return *this;
}

Polynomial Polynomial::operator/(const Polynomial& rhs) const {
    Polynomial dividend = *this, divisor = rhs, res;
    dividend.complicate();
    divisor.complicate();
    res.justify();
    if (divisor.empty() || divisor.items.front()->exponent > dividend.items.front()->exponent) {
        return res;
    }

    while (!dividend.empty() && dividend.items.front()->exponent >= divisor.items.front()->exponent) {
        Item t = dividend.items.front()->operator/(*(divisor.items.front()));
        res.append(t);
        auto sub = (divisor * t);
        dividend = dividend - sub;
    }

    return res;
}

Polynomial Polynomial::operator/=(const Polynomial& rhs)
{
    auto res = this->operator/(rhs);
    items = res.items;
    return *this;
}

Polynomial Polynomial::power(int n) const
{
    if (n <= 0) { return {}; }

    Polynomial res = *this;
    for (int i = 1; i < n; i++) {
        res *= *this;
    }

    return res;
}

template <typename T>
T Polynomial::value(T x) const
{
    T res = 0;
    for (const auto& item : items) {
        res += item->value<T>(x);
    }
    return res;
}

Polynomial Polynomial::derivative() const
{
    Polynomial res;
    for (const auto& item : items) {
        res.append(item->derivative());
    }
    return res;
}

Polynomial Polynomial::maclaurinExpansion() const
{
    if (items.empty()) { return {}; }

    Polynomial res, der = *this;
    int factorial = 1;
    for (int exp = 0; !der.empty(); exp++) {
        if (exp != 0) {
            factorial *= exp;
        }
        res.append(der.value(0) / factorial, exp, false);
        der = der.derivative();
    }

    return res;
}
