#pragma once
#include <iostream>
#include <string>
#include <source_location>

namespace BenScr {
	enum class LogLevel {
		Info,
		Warning,
		Error
	};

	class Debug {
	public:
		template<typename... Args>
		static void Log(LogLevel level = LogLevel::Info, Args&&... args) {
			DateTime now = DateTime::Now();

			switch (level) {
			case LogLevel::Info:
				std::cout << "[" << now.ToTimeString() << "][INFO] ";
				break;

			case LogLevel::Warning:
				std::cout << "[" << now.ToTimeString() << "][WARNING] ";
				break;

			case LogLevel::Error:
				std::cout << "[" << now.ToTimeString() << "][ERROR] ";
				break;
			}
			(std::cout << ... << args);
			std::cout << '\n';
		}
	};
}