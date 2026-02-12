#include "File.hpp"
#include <filesystem>

namespace BenScr {
	bool File::Exists(const std::string& path) {
		return std::filesystem::exists(path);
	}


	void File::WriteAllText(const std::string& path, const std::string& text) {
		std::ofstream file(path);

		if (!file.is_open()) {
			throw std::runtime_error("File couldn't be opened");
		}

		file.write(text.c_str(), text.size());
		file.close();
	}

	std::string File::ReadAllText(const std::string& path) {
		std::ifstream file(path, std::ios::ate);

		if (!file.is_open()) {
			throw std::runtime_error("File couldn't be opened");
		}

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::string buffer(size, '\0');
		file.read(buffer.data(), size);

		file.close();
		return buffer;
	}

	std::vector<std::uint8_t> File::ReadAllBytes(const std::string& path) {
		std::ifstream file(path, std::ios::binary | std::ios::ate);

		if (!file.is_open()) {
			throw std::runtime_error("File couldn't be opened");
		}

		std::streamsize size = file.tellg();

		if (size < 0) {
			throw std::runtime_error("tellg() failed");
		}

		file.seekg(0, std::ios::beg);

		std::vector<std::uint8_t> buffer(static_cast<std::size_t>(size));
		
		if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
			throw std::runtime_error("File reading failed");
		}

		file.close();
		return buffer;
	}
}