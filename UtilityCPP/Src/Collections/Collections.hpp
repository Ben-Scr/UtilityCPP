#pragma once

namespace BenScr {
	using string = std::string;
	using byte = unsigned char;
	using ushort = uint16_t;
	using uint = uint32_t;
	using ulong = uint64_t;

	template<class T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> MaxValue() { return std::numeric_limits<T>::max(); }

	template<class T>
	std::enable_if_t<std::is_arithmetic_v<T>, T> MinValue() { return std::numeric_limits<T>::min(); }


}