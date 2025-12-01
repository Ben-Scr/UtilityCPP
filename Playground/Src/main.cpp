#include <iostream>
#include <unordered_map>
#include <functional>

#include "Collections/Types.hpp"

#include "Utility/Console.hpp"
#include "Utility/String.hpp"
#include "Utility/Converter.hpp"

#include "Math/Random.hpp"

using namespace BenScr;


bool canExit = false;

void RandomExample() {
	Random rand = Random();

	Console::WriteLine("Random Number [1 - 100]: ", rand.Next<int>(1, 100));
	Console::WriteLine("Random Number [0.0f - 1.0f]: ", rand.Next<float>(.0f, 1.0f));
}

void Exit() {
	Console::WriteLine("Exiting...");
	canExit = true;
}

std::unordered_map<std::string, std::function<void()>> functionMap{
	{ "Random", RandomExample },
	{ "Exit", Exit }
};

void PressEnterToContinue()
{
	Console::WriteLine("Press Enter to continue...");
	Console::ReadLine();
}

void DisplayOptions() {
	Console::WriteLine("Choose one of the following options (1-", functionMap.size(), ")");
	Console::WriteLine(String::SEPERATOR_40);

	int i = 0;
	for (const auto& pair : functionMap) {
		Console::WriteLine(++i, ") ", pair.first);
	}

	Console::WriteLine(String::SEPERATOR_40);
	std::string input = Console::ReadLine();

	i = 0;
	int choice = 0;
	if (Converter::TryConvertTo<int>(input, choice)) {
		for (const auto& pair : functionMap) {
			if (choice == ++i) {
				Console::WriteLine("You choose ", pair.first);
				Console::WriteLine(String::SEPERATOR_40);
				pair.second();
				break;
			}
		}
	}

	Console::WriteLine(String::SEPERATOR_40);
	PressEnterToContinue();
	Console::Clear();
}

bool EnteredYes()
{
	bool enteredYes = false;
	enteredYes = String::ToLower(Console::ReadLine()) == "y";
	return enteredYes;
}

void Run() {
	while (!canExit) {
		Console::WriteLine(String::SEPERATOR_40);
		DisplayOptions();
	}
}

int main()
{
	Run();
	return 0;
}