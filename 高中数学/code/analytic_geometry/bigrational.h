#pragma once

#include "bigint.h"
#include "rational.h"

namespace math {

template <>
Rational<BigInt> sqrt(const Rational<BigInt>& r) {
    BigInt p = sqrt(r.p / r.q);
    return { p, 1 };
}



}
