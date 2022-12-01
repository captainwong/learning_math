#pragma once

#include <list>
#include <algorithm>
#include <memory>
#include <string>

// 多项式的一项如 2x^3
struct Item {
    int coefficient{}; // 系数
    int exponent{}; // 指数

    Item operator*(const Item& rhs) const {
        return Item{ coefficient * rhs.coefficient, exponent + rhs.exponent };
    }

    Item& operator*=(const Item& rhs) {
        coefficient *= rhs.coefficient;
        exponent += rhs.exponent;
        return *this;
    }

    Item operator/(const Item& rhs) const {
        return Item{ coefficient / rhs.coefficient, exponent - rhs.exponent };
    }

    Item& operator/=(const Item& rhs) {
        coefficient /= rhs.coefficient;
        exponent -= rhs.exponent;
        return *this;
    }

    // 代入x求值
    template <typename T = int>
    T value(T x) const {
        return (T)(coefficient * pow(x, exponent));
    }

    // 求导
    Item derivative() const {
        return Item{ coefficient * exponent, exponent ? (exponent - 1): 0 };
    }

    // 2 3
    std::string toString() const {
        return std::to_string(coefficient) + " " + std::to_string(exponent);
    }

    // 2x^3
    std::string toString2(bool with_pm = true) const {
        if (coefficient == 0) { return {}; }
        std::string res;
        if (with_pm) {
            res += coefficient > 0 ? "+" : "-";
        }
        int c = abs(coefficient);
        if (exponent != 0) {
            if (c != 1) {
                res += std::to_string(c);
            }
            res += "x";
            if (exponent != 1) {
                res += "^";
                res += std::to_string(exponent);
            }
        } else {
            res += std::to_string(c);
        }
        return res;
    }
};

using ItemPtr = std::shared_ptr<Item>;

struct Polynomial {
    std::list<ItemPtr> items{};

    bool empty() const {
        return items.empty() || (items.size() == 1 && items.front()->coefficient == 0);
    }

    void append(Item item, bool force = false);

    void append(int coefficient, int exponent, bool force = false) {
        return append(Item{ coefficient, exponent }, force);
    }

    // 以指数递降排列
    void sort() {
        items.sort([](const ItemPtr& a, const ItemPtr& b) {
            return a->exponent > b->exponent;
        });
    }

    // 以指数递增排列
    void rsort() {
        items.sort([](const ItemPtr& a, const ItemPtr& b) {
            return a->exponent < b->exponent;
        });
    }

    // 无元素时以{0, 0}表示
    void justify() {
        if (items.empty()) {
            items.push_back(std::make_shared<Item>(Item{ 0, 0 }));
        }
    }

    // 化简，合并同类项、消除零系数项
    void simplify();

    // 化繁，使得从最高次幂到最低次幂，每项都有元素（以系数为0的元素填充）
    void complicate();

    Polynomial operator+(const Polynomial& rhs) const;
    Polynomial operator+=(const Polynomial& rhs);
    Polynomial operator-(const Polynomial& rhs) const;
    Polynomial operator-=(const Polynomial& rhs);
    Polynomial operator*(const Item& rhs) const;
    Polynomial operator*=(const Item& rhs);
    Polynomial operator*(const Polynomial& rhs) const;
    Polynomial operator*=(const Polynomial& rhs);
    Polynomial operator/(const Polynomial& rhs) const;
    Polynomial operator/=(const Polynomial& rhs);

    // 乘方
    Polynomial power(int n) const;

    // 代入x求值

    template <typename T = int>
    T value(T x) const;

    // 求一阶导数
    Polynomial derivative() const;

    // 麦克劳林 (Maclaurin) 展开
    Polynomial maclaurinExpansion() const;

    // TODO: 支持非零的幂展开，需要 items 中包含未化简的多项式元素，得大改

    // 1 2 -3 1 1 0
    std::string toString() const {
        if (items.empty()) { return {}; }
        auto iter = items.begin();
        std::string res = (*iter)->toString();
        while (++iter != items.end()) {
            res += " " + (*iter)->toString();
        }
        return res;
    }

    // x^2 - 3x + 1
    std::string toString2() const {
        if (items.empty()) { return {}; }
        auto iter = items.begin();
        std::string res;
        if ((*iter)->coefficient < 0) { res.push_back('-'); }
        res += (*iter)->toString2(false);        

        while (++iter != items.end()) {
            res.push_back(' ');
            res.push_back((*iter)->coefficient < 0 ? '-' : '+');
            res.push_back(' ');
            res += (*iter)->toString2(false);
        }
        return res;
    }
};
