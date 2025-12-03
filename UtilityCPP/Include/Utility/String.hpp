#pragma once
#include <algorithm>
#include <cctype>
#include <string>

namespace BenScr {
	class String
	{
	public:
		static constexpr const char* SEPERATOR_20 = "--------------------";
		static constexpr const char* SEPERATOR_40 = "----------------------------------------";
		static constexpr const char* DIGITS = "0123456789";
		static constexpr const char* UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		static constexpr const char* LOWER = "abcdefghijklmnopqrstuvwxyz";
		static constexpr const char* SYMBOLS = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

		static std::string ToLower(std::string text)
		{
			std::transform(text.begin(), text.end(), text.begin(),
				[](unsigned char c) { return std::tolower(c); });

			return text;
		}

		template<typename... Args>
		static std::string ToString(Args&&... args)
		{
			std::ostringstream stream;
			(stream << ... << args);
			return stream.str();
		}

		static std::string ToUpper(std::string text)
		{
			std::transform(text.begin(), text.end(), text.begin(),
				[](unsigned char c) { return std::toupper(c); });

			return text;
		}

		static std::string Trim(std::string text)
		{
			return text;
		}

		static std::string Replace(std::string text, std::string toReplace) {
			return text;
		}

		static bool StartsWith(std::string text, std::string toFind) {
			return text.rfind(toFind, 0) == 0;
		}

		static bool Contains(std::string& text, std::string& toFind) {
			return text.find(toFind) != std::string::npos;
		}
	};
}