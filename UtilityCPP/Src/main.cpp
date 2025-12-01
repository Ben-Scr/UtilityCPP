#include <iostream>
#include "File/File.hpp"
#include "File/Serializer.hpp"
#include "Math/Random.hpp"
#include "Utility/Converter.hpp"
#include "Collections/Collections.hpp"

using namespace BenScr;

struct Vec2 {
	float x;

	Vec2() {};
	Vec2(float x) : x(x) {}

	bool operator<(const Vec2& other) const {
		return x < other.x;
	}
	bool operator>(const Vec2& other) const {
		return x > other.x;
	}
	Vec2 operator+(const Vec2& other) const {
		return Vec2(x + other.x);
	}
};

int main()
{
	byte bytes[]{ 25, 31,12,12 };
	std::cout << "Converted f: " << ConvertFromBytes<string>(bytes) << std::endl;
	std::cout << "Max value of uint: " << MinValue<long long>() << std::endl;
	float randomInt = Random().Next<uint>(0, 6);
	std::cout << "Random Int: " << randomInt << std::endl;

	const std::array<string, 5> lines = { "Line 1", "Line 2" ,"Line 3" ,"Line 4" ,"Line 5" };

	//File::WriteAllText("Test.txt", "Hello World!");
	//File::WriteAllLines("Lines.txt", lines);
	//File::WriteAllBytes("Bytes.txt", bytes);

	//std::cout << File::ReadAllText("Test.txt");
}