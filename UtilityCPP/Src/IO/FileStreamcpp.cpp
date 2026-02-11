#include "FileStream.hpp"

namespace BenScr {
	// in -> Opens for reading
	// out -> Opens for writing
	// app -> Append -> Writes to the end of a file
	// trunc -> Truncate -> Empties file when opening
	// binary -> No text translation (no crlf conversion on windows '\n')

	FileStream::FileStream(const std::string& path,std::ios::openmode mode) {
		ofstream = std::ofstream(path, mode);
	}
}