#pragma once
#include<limits>

namespace BenScr {
	template<class T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> MaxValue() { return std::numeric_limits<T>::max(); }

	template<class T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> MinValue() { return std::numeric_limits<T>::min(); }
}