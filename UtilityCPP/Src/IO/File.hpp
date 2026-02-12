#pragma once
#include <fstream>
#include <iostream>

#include<string>
#include<array>
#include <vector>

namespace BenScr {
	class File {
	public:
		static bool Exists(const std::string& path);


		static void WriteAllText(const std::string& path, const std::string& text);

		template<size_t Size>
		static void WriteAllLines(const std::string& path, const std::array<std::string, Size> lines) {
			std::ofstream file(path);

			if (!file.is_open()) {
				throw std::runtime_error("File couldn't be opened");
			}

			for (const std::string& line : lines) {
				file.write(line.c_str(), line.size());
				file.write("\n", 1);
			}

			file.close();
		}

		template<size_t Size>
		static void WriteAllBytes(const std::string& path, const std::array<std::uint8_t, Size> bytes) {
			std::ofstream file(path, std::ios::binary);

			if (!file.is_open()) {
				throw std::runtime_error("File couldn't be opened");
			}

			file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
			file.close();
		}

		template<typename T>
		static void WriteT(const std::string& path, const T& obj) {

		}

		static std::string ReadAllText(const std::string& path);
		static std::vector<std::uint8_t> ReadAllBytes(const std::string& path);
	};
}