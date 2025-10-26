#include <iostream>
#include "IOS/File.hpp"
#include "IOS/Serializer.hpp"
#include "Math/Random.hpp"

using namespace UtilityCPP;

class Vec2 {
	float x;
};

int main()
{
	int randomInt = Random().NextInt();
	std::cout << "Random Int: " << randomInt << std::endl;

	const std::array<std::string, 5> lines = { "Line 1", "Line 2" ,"Line 3" ,"Line 4" ,"Line 5" };
	const std::array<uint8_t, 7> bytes = { 1, 2, 254, 251, 12, 144, 0 };

	File::WriteAllText("Test.txt", "Hello World!");
	File::WriteAllLines("Lines.txt", lines);
	File::WriteAllBytes("Bytes.txt", bytes);

	Serializer::Serialize<Vec2>("Serialized.txt", Vec2());

	std::cout << File::ReadAllText("Test.txt");
}