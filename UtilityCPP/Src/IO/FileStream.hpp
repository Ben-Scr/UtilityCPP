#pragma once
#include<string>
#include <fstream>

namespace BenScr {
	
	class FileStream {
	public:
		FileStream(const std::string& path, std::ios::openmode mode);

		void Close();
		const bool IsOpen() const { return ofstream.is_open(); };
	private:
		std::ofstream ofstream;
	};
}