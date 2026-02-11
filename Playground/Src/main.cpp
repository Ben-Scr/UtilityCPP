#include <iostream>
#include <unordered_map>
#include <functional>

#include "Utility/Console.hpp"
#include "IO/FileStream.hpp"

#include "Time/TimeSpan.hpp"
#include "Time/DateTime.hpp"
#include "Time/Timer.hpp"

#include "Utility/StringHelper.hpp"
#include "Utility/Converter.hpp"

#include "Math/Random.hpp"

using namespace BenScr;


bool canExit = false;
Timer timer = Timer();


bool EnteredYes()
{
	bool enteredYes = false;
	enteredYes = StringHelper::ToLower(Console::ReadLine()) == "y";
	return enteredYes;
}

void RandomExample() {
	Console::WriteLine("Random Number [1 - 100]: ", Random::NextInt32(1, 100));
	Console::WriteLine("Random Number [0.0f - 1.0f]: ", Random::NextFloat(.0f, 1.0f));
}

void StringExample() {
	std::string sample = "  Hello, UtilityCPP!  ";
	Console::WriteLine("Original String: '", sample, "'");
	Console::WriteLine("Trimmed String: '", StringHelper::Trim(sample), "'");
	Console::WriteLine("Uppercase String: '", StringHelper::ToUpper(sample), "'");
	Console::WriteLine("Lowercase String: '", StringHelper::ToLower(sample), "'");
}

void TimerExample() {
	Console::WriteLine("Elasped time since startup: ", StringHelper::ToString(timer));
}

void DateTimeExample() {
	DateTime dayTime = DateTime::Now();
	Console::WriteLine("Current Date and Time:");
	Console::WriteLine(dayTime.ToShortString());
	Console::WriteLine("Current day of week: ", dayTime.GetWeekDayString());
}

void TimeSpanExample() {
	Console::WriteLine("Timespan(0(h), 0(m), 1000(s))");

	
	TimeSpan span = TimeSpan(0, 0, 1000);
	Console::WriteLine(span.ToShortString());
}

void Exit() {
	Console::WriteLine("Are you sure you want to exit? (y/n): ");
	if (!EnteredYes()) return;
	Console::WriteLine("Exiting...");
	canExit = true;
}

std::unordered_map<std::string, std::function<void()>> functionMap{
	{ "Random", RandomExample },
	{ "String",StringExample },
	{ "Timer", TimerExample },
	{ "DateTime",DateTimeExample },
	{ "TimeSpan", TimeSpanExample },
	{ "Exit", Exit }
};


void PressEnterToContinue()
{
	Console::WriteLine("Press Enter to continue...");
	Console::ReadLine();
}

void DisplayOptions() {
	Console::WriteLine("Choose one of the following options (1-", functionMap.size(), ")");
	//Console::WriteLine(StringHelper::SEPERATOR_40);

	int i = 0;
	for (const auto& pair : functionMap) {
		Console::WriteLine(++i, ") ", pair.first);
	}

	//Console::WriteLine(StringHelper::SEPERATOR_40);
	std::string input = Console::ReadLine();
	Console::Clear();

	i = 0;
	int choice = 0;
	if (Converter::TryConvertTo<int>(input, choice)) {
		for (const auto& pair : functionMap) {
			if (choice == ++i) {
				Console::WriteLine("You choose ", pair.first);
				//Console::WriteLine(String::SEPERATOR_40);
				pair.second();
				break;
			}
		}
	}
	else {
		Console::WriteLine("Invalid input");
	}

	//Console::WriteLine(String::SEPERATOR_40);

	if (!canExit) {
		PressEnterToContinue();
		Console::Clear();
	}
}

void Run() {
	while (!canExit) {
		Console::SetTitle("Utility CPP");
		//Console::WriteLine(String::SEPERATOR_40);
		DisplayOptions();
	}
}

int main()
{
	const FileStream fs = FileStream("Test.txt", std::ios::trunc);
	bool b = fs.IsOpen();

	Run();
	return 0;
}