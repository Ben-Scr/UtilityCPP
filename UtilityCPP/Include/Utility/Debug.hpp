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
		static void Log(Args&&... args) {

			//switch (level) {
			//case LogLevel::Info:
			//	std::cout << "[INFO] ";
			//	break;

			//case LogLevel::Warning:
			//	std::cout << "[WARNING] ";
			//	break;

			//case LogLevel::Error:
			//	std::cout << "[ERROR] ";
			//	break;
			//}
			(std::cout << ... << args);
			std::cout << '\n';
		}
	};
}