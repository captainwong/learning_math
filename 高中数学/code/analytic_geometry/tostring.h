#pragma once

#include <string>

namespace math {

template <typename T>
inline std::string toString(T&& t) {
	return std::to_string(std::forward<T>(t));
}

}
