#include <iostream>


namespace BenScr {
	class Converter {
	public:
		template<class T>
		static std::enable_if_t<std::is_arithmetic_v<T>, T> ConvertTo(const std::string& str) {
			if constexpr (std::is_same_v<T, int>) {
				return std::stoi(str);
			}
			else if constexpr (std::is_same_v<T, long>) {
				return std::stol(str);
			}
			else if constexpr (std::is_same_v<T, long long>) {
				return std::stoll(str);
			}
			else if constexpr (std::is_same_v<T, unsigned int>) {
				return static_cast<unsigned int>(std::stoul(str));
			}
			else if constexpr (std::is_same_v<T, unsigned long>) {
				return std::stoul(str);
			}
			else if constexpr (std::is_same_v<T, unsigned long long>) {
				return std::stoull(str);
			}
			else if constexpr (std::is_same_v<T, float>) {
				return std::stof(str);
			}
			else if constexpr (std::is_same_v<T, double>) {
				return std::stod(str);
			}
			else if constexpr (std::is_same_v<T, long double>) {
				return std::stold(str);
			}
			else {
				static_assert(sizeof(T) == 0, "Unsupported type for ConvertTo");
			}
		}

		template<class T>
		static bool TryConvertTo(const std::string& str, std::enable_if_t<std::is_arithmetic_v<T>, T>& out) {
			try {
				out = ConvertTo<T>(str);
				return true;
			}
			catch (...) {
				return false;
			}
		}



		template<class T>
		std::enable_if_t<std::is_arithmetic_v<T>, std::string> ConvertToString(const T& value) {
			return std::to_string(value);
		}

		template <class T>
		T ConvertFromBytes(const uint8_t* bytes)
		{
			T value;
			std::memcpy(&value, bytes, sizeof(T));
			return value;
		}
	};
}