#include "File.hpp"

namespace UtilityCPP {
	void File::WriteAllText(const std::string& path, const std::string& text) {
		std::ofstream file(path);

		if (!file.is_open()) {
			return;
		}

		file.write(text.c_str(), text.size());
		file.close();
	}

    std::string File::ReadAllText(const std::string& path) {
        std::ifstream file(path, std::ios::ate);
        if (!file.is_open()) {
            std::cerr << "File couldn't be opened\n";
            return {};
        }

        std::streamsize size = file.tellg(); 
        file.seekg(0, std::ios::beg);

        std::string buffer(size, '\0');
        file.read(buffer.data(), size);

        return buffer;
    }
}