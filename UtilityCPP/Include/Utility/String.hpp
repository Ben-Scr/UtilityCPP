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

        static std::string ToLower(std::string text)
        {
            std::transform(text.begin(), text.end(), text.begin(),
                [](unsigned char c) { return std::tolower(c); });

            return text;
        }
        static std::string ToUpper(std::string text)
        {
            std::transform(text.begin(), text.end(), text.begin(),
                [](unsigned char c) { return std::toupper(c); });

            return text;
        }
    };
}