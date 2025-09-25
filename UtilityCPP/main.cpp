#include <iostream>
#include "IOS/File.hpp"

using namespace UtilityCPP;

int main()
{
	const std::array<std::string, 5> lines = { "Line 1", "Line 2" ,"Line 3" ,"Line 4" ,"Line 5" };
	const std::array<uint8_t, 7> bytes = { 1, 2, 254, 251, 12, 144, 0 };

	File::WriteAllText("Test.txt", "Hello World!");
	File::WriteAllLines("Lines.txt", lines);
	File::WriteAllBytes("Bytes.txt", bytes);

	std::cout << File::ReadAllText("Test.txt");
}