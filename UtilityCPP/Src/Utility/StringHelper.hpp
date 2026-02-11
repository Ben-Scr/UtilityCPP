#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <stdexcept>

namespace BenScr {
	class StringHelper
	{
	public:
		static std::string WrapWith(std::string_view s, char mark) {
			std::string out;
			out.reserve(s.size() + 2);
			out.push_back(mark);
			out.append(s);
			out.push_back(mark);
			return out;
		}

		static std::string WrapWith(std::string_view s, char markBegin, char markEnd) {
			std::string out;
			out.reserve(s.size() + 2);
			out.push_back(markBegin);
			out.append(s);
			out.push_back(markEnd);
			return out;
		}

		static std::string WrapWith(std::string_view s, std::string_view mark) {
			std::string result;
			result.reserve(s.size() + (mark.size() * 2));
			result += mark;
			result += s;
			result += mark;
			return result;
		}

		static std::string WrapWith(std::string_view s, std::string_view markBegin, std::string_view markEnd) {
			std::string result;
			result.reserve(s.size() + (markBegin.size() + markEnd.size()));
			result += markBegin;
			result += s;
			result += markEnd;
			return result;
		}


		template <typename... Args>
		static std::string ToString(Args&&... args) {
			std::ostringstream oss;
			((oss << std::forward<Args>(args)), ...);
			return oss.str();
		}
		template <typename... Args>
		static char* ToCharString(Args&&... args) {
			std::ostringstream oss;
			((oss << std::forward<Args>(args)), ...);
			return oss.str();
		}

		static std::string ToLower(const std::string& str) {
			std::string result = str;
			std::transform(result.begin(), result.end(), result.begin(),
				[](unsigned char c) { return std::tolower(c); });
			return result;
		}
		static std::string ToUpper(const std::string& str) {
			std::string result = str;
			std::transform(result.begin(), result.end(), result.begin(),
				[](unsigned char c) { return std::toupper(c); });
			return result;
		}

		static bool EndsWith(const std::string& str, const std::string& suffix) {
			if (suffix.size() > str.size()) return false;
			return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
		}
		static bool StartsWith(const std::string& str, const std::string& prefix) {
			if (prefix.size() > str.size()) return false;
			return std::equal(prefix.begin(), prefix.end(), str.begin());
		}

		static std::string Replace(const std::string& str, const std::string& to) {
			return str;
		}

		static std::string Trim(const std::string& text)
		{
			size_t start = 0;
			size_t end = text.size();

			while (start < end && std::isspace(static_cast<unsigned char>(text[start])))
				++start;

			while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])))
				--end;

			return text.substr(start, end - start);
		}


		static std::string ToIEC(std::size_t size)
		{
			const double s = static_cast<double>(size);
			constexpr double k = 1024.0;
			constexpr double m = k * k;
			constexpr double g = m * k;
			constexpr double t = g * k;

			if (s < k) return ToString(s, " B");
			if (s < m) return ToString(s / k, " KiB");
			if (s < g) return ToString(s / m, " MiB");
			if (s < t) return ToString(s / g, " GiB");
			return ToString(s / t, " TiB");
		}

		static std::string ToSI(std::size_t size) {
			const double s = static_cast<double>(size);

			if (s < 1000.0) return ToString(s, " B");
			if (s < 1e6)    return ToString(s / 1e3, " kB");
			if (s < 1e9)    return ToString(s / 1e6, " MB");
			if (s < 1e12)   return ToString(s / 1e9, " GB");
			return ToString(s / 1e12, " TB");
		}

		static std::string Replace(std::string text, std::string toReplace) {
			throw std::exception("Not implemented yet!");
			std::string result = text;
			return result;
		}

		static bool Contains(std::string& text, std::string& toFind) {
			return text.find(toFind) != std::string::npos;
		}
	};

	inline std::ostream& operator<<(std::ostream& oss, const std::vector<std::uint8_t>& vec) {
		const auto size = vec.size();

		oss << "[" << static_cast<int>(vec[0]);

		for (auto i{ 1uz }; i < size; i++) {
			oss << ", " << static_cast<int>(vec[i]);
		}
		
		oss << "]";

		return oss;
	}
}