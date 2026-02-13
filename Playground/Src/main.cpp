#include <iostream>
#include <unordered_map>
#include <functional>

#include "Utility/Console.hpp"

#include "IO/File.hpp"

#include "Time/TimeSpan.hpp"
#include "Time/DateTime.hpp"
#include "Time/Timer.hpp"

#include "Utility/StringHelper.hpp"
#include "Utility/Converter.hpp"

#include "Utility/Limits.hpp"
#include "Math/Random.hpp"
#include "Collections/Types.hpp"
#include "Collections/Array.hpp"

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
	Console::WriteLine(dayTime.ToDateTimeString());
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

void FileTest() {
	Console::WriteLine("Enter a text you want to save in storage:");
	std::string input = Console::ReadLine();
	File::WriteAllText("Test.txt", input);
	Console::WriteLine("Saved txt file output: ", File::ReadAllText("Test.txt"));


	File::WriteAllBytes("Test.bin", std::array<std::uint8_t, 13>{1, 2, 3});
	Console::WriteLine("Saved bin file output:", File::ReadAllBytes("Test.bin"));
}

void Limits() {
	Console::WriteLine("Unsigned integer max values:");
	Console::WriteLine("u8: ", MaxValue<u8>());
	Console::WriteLine("u16: ", MaxValue<u16>());
	Console::WriteLine("u32: ", MaxValue<u32>());
	Console::WriteLine("u64: ", MaxValue<u64>());
	Console::WriteLine("\nInteger max values:");
	Console::WriteLine("i8: ", MaxValue<i8>());
	Console::WriteLine("i16: ", MaxValue<i16>());
	Console::WriteLine("i32: ", MaxValue<i32>());
	Console::WriteLine("i64: ", MaxValue<i64>());

	Console::WriteLine("\nUnsigned integer min values:");
	Console::WriteLine("u8: ", MinValue<u8>());
	Console::WriteLine("u16: ", MinValue<u16>());
	Console::WriteLine("u32: ", MinValue<u32>());
	Console::WriteLine("u64: ", MinValue<u64>());
	Console::WriteLine("\nInteger min values:");
	Console::WriteLine("i8: ", MinValue<i8>());
	Console::WriteLine("i16: ", MinValue<i16>());
	Console::WriteLine("i32: ", MinValue<i32>());
	Console::WriteLine("i64: ", MinValue<i64>());
}


void ChangeTitle() {
	Console::WriteLine("Input the new Title:");
	std::string input = Console::ReadLine();
	Console::SetTitle(input);
}

std::vector<std::pair<std::string, std::function<void()>>> functionMap = {
	{ "Random", RandomExample },
	{ "String",StringExample },
	{ "Timer", TimerExample },
	{ "DateTime",DateTimeExample },
	{ "TimeSpan", TimeSpanExample },
	{ "Limits" , Limits},
	{ "File", FileTest },
	{ "ChangeTitle", ChangeTitle},
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
		//Console::WriteLine(String::SEPERATOR_40);
		DisplayOptions();
	}
}

int main()
{ 
	Array<int, 10> arr = Array<int, 10>(1);
	auto arr2D = Array<Array<int, 5>, 2>{};
	Console::WriteLine(arr);
	Console::WriteLine(arr2D);
	Console::ReadLine();
	Run();
	return 0;
}