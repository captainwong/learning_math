#pragma once

#include <list>
#include <algorithm>
#include <memory>
#include <string>

// ����ʽ��һ���� 2x^3
struct Item {
    int coefficient{}; // ϵ��
    int exponent{}; // ָ��

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

    // ����x��ֵ
    template <typename T = int>
    T value(T x) const {
        return (T)(coefficient * pow(x, exponent));
    }

    // ��
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

    // ��ָ���ݽ�����
    void sort() {
        items.sort([](const ItemPtr& a, const ItemPtr& b) {
            return a->exponent > b->exponent;
        });
    }

    // ��ָ����������
    void rsort() {
        items.sort([](const ItemPtr& a, const ItemPtr& b) {
            return a->exponent < b->exponent;
        });
    }

    // ��Ԫ��ʱ��{0, 0}��ʾ
    void justify() {
        if (items.empty()) {
            items.push_back(std::make_shared<Item>(Item{ 0, 0 }));
        }
    }

    // ���򣬺ϲ�ͬ���������ϵ����
    void simplify();

    // ������ʹ�ô���ߴ��ݵ���ʹ��ݣ�ÿ���Ԫ�أ���ϵ��Ϊ0��Ԫ����䣩
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

    // �˷�
    Polynomial power(int n) const;

    // ����x��ֵ

    template <typename T = int>
    T value(T x) const;

    // ��һ�׵���
    Polynomial derivative() const;

    // ������� (Maclaurin) չ��
    Polynomial maclaurinExpansion() const;

    // TODO: ֧�ַ������չ������Ҫ items �а���δ����Ķ���ʽԪ�أ��ô��

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
