#pragma once
#include <fstream>
#include <iostream>
#include<string>

namespace UtilityCPP {
	class Serializer {
	public:
		template<typename T>
        static void Serialize(const std::string& path, const T& obj) {
            std::ofstream file(path, std::ios::binary);
            if (!file.is_open()) {
                std::cerr << "Error";
                return;
            }

            file.write(reinterpret_cast<const char*>(&obj), sizeof(T));
        }
	};
}