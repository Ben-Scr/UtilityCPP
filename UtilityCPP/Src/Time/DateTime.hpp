#pragma once
#include <chrono>

namespace BenScr {
	enum class DayOfWeek {
		Sunday = 0,
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6
	};

	struct DateTime {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		int millisecond;
		int microsecond;

		static DateTime Now() {
			auto now = std::chrono::system_clock::now();

			std::time_t now_c = std::chrono::system_clock::to_time_t(now);
			std::time_t t = std::time(nullptr);

			std::tm localTime;
			localtime_s(&localTime, &t);


			auto duration = now.time_since_epoch();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
			auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000;
			return DateTime{
				localTime.tm_year + 1900,
				localTime.tm_mon + 1,
				localTime.tm_mday,
				localTime.tm_hour,
				localTime.tm_min,
				localTime.tm_sec,
				static_cast<int>(milliseconds),
				static_cast<int>(microseconds)
			};
		}

		static int GetWeekday(int year, int month, int day)
		{
			if (month < 3)
			{
				month += 12;
				year--;
			}

			int K = year % 100;
			int J = year / 100;

			int h = (day + 13 * (month + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
			int weekday = (h + 6) % 7;
			return weekday;
		}
		int GetWeekday() const
		{
			int day = this->day;
			int year = this->year;
			int month = this->month;

			if (month < 3)
			{
				month += 12;
				year--;
			}

			int K = year % 100;
			int J = year / 100;

			int h = (day + 13 * (month + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
			int weekday = (h + 6) % 7;
			return weekday;
		}

		std::string GetWeekDayString() const {
			static const char* daysOfWeek[] = {
				"Sunday", "Monday", "Tuesday", "Wednesday",
				"Thursday", "Friday", "Saturday"
			};
			int weekday = GetWeekday();
			return daysOfWeek[weekday];
		}

		std::string ToDateString() const {
			return std::to_string(year) + "-" +
				(month < 10 ? "0" : "") + std::to_string(month) + "-" +
				(day < 10 ? "0" : "") + std::to_string(day);
		}

		std::string ToTimeString() const {
			return (hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
				(minute < 10 ? "0" : "") + std::to_string(minute) + ":" +
				(second < 10 ? "0" : "") + std::to_string(second);
		}

		std::string ToShortString() const {
			return std::to_string(year) + "-" +
				(month < 10 ? "0" : "") + std::to_string(month) + "-" +
				(day < 10 ? "0" : "") + std::to_string(day) + " " +
				(hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
				(minute < 10 ? "0" : "") + std::to_string(minute) + ":" +
				(second < 10 ? "0" : "") + std::to_string(second);
		}

		std::string ToString() const {
			return std::to_string(year) + "-" +
				(month < 10 ? "0" : "") + std::to_string(month) + "-" +
				(day < 10 ? "0" : "") + std::to_string(day) + " " +
				(hour < 10 ? "0" : "") + std::to_string(hour) + ":" +
				(minute < 10 ? "0" : "") + std::to_string(minute) + ":" +
				(second < 10 ? "0" : "") + std::to_string(second) + "." +
				std::to_string(millisecond) + std::to_string(microsecond);
		}
	};
}