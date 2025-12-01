#pragma once
#include <fstream>
#include <iostream>
#include<string>
#include<array>

namespace BenScr {
	// Static class
	class File {
	public:
		static void WriteAllText(const std::string& path, const std::string& text);

		template<size_t size>
		static void WriteAllLines(const std::string& path, const std::array<std::string, size> lines) {
			std::ofstream file(path);

			if (!file.is_open()) {
				return;
			}

			for (const std::string& line : lines) {
				file.write(line.c_str(), line.size());
				file.write("\n", 1);
			}

			file.close();
		}

		template<size_t size>
		static void WriteAllBytes(const std::string& path, const std::array<char, size> bytes) {
			std::ofstream file(path, std::ios::binary);

			if (!file.is_open()) {
				return;
			}

			file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
			file.close();
		}


		static std::string ReadAllText(const std::string& path);
	};
}