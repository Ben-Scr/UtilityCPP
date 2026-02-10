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

	struct Date {
		int Year;
		int Month;
		int Day;

		Date(int year, int month, int day) : Year{ year }, Month{ month }, Day{ day } {

		}
	};

	struct DateTime {
		static DateTime Now() {
			const auto now = std::chrono::system_clock::now();

			const std::chrono::sys_days day_point = floor<std::chrono::days>(now);
			const std::chrono::year_month_day ymd{ day_point };

			const auto tod = now - day_point;
			const auto us = duration_cast<std::chrono::microseconds>(tod).count();

			std::uint64_t tmp = static_cast<std::uint64_t>(us);

			const std::uint32_t micro = static_cast<std::uint32_t>(tmp % 1000); tmp /= 1000;
			const std::uint32_t milli = static_cast<std::uint32_t>(tmp % 1000); tmp /= 1000;
			const std::uint32_t sec = static_cast<std::uint32_t>(tmp % 60);   tmp /= 60;
			const std::uint32_t min = static_cast<std::uint32_t>(tmp % 60);   tmp /= 60;
			const std::uint32_t hour = static_cast<std::uint32_t>(tmp % 24);

			return DateTime{
			  static_cast<std::uint32_t>(static_cast<int>(ymd.year())),
			  static_cast<std::uint32_t>(static_cast<unsigned>(ymd.month())),
			  static_cast<std::uint32_t>(static_cast<unsigned>(ymd.day())),
			  hour,
			  min,
			  sec,
			  milli,
			  micro,
			};
		}

		static int GetWeekday(Date date)
		{
			if (date.Month < 3)
			{
				date.Month += 12;
				date.Year--;
			}

			int K = date.Year % 100;
			int J = date.Year / 100;

			int h = (date.Day + 13 * (date.Month + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
			int weekday = (h + 6) % 7;
			return weekday;
		}

		int GetWeekday() const
		{
			int day = this->Day;
			int year = this->Year;
			int month = this->Month;

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
			return std::to_string(Year) + "-" +
				(Month < 10 ? "0" : "") + std::to_string(Month) + "-" +
				(Day < 10 ? "0" : "") + std::to_string(Day);
		}

		std::string ToTimeString() const {
			return (Hour < 10 ? "0" : "") + std::to_string(Hour) + ":" +
				(Minute < 10 ? "0" : "") + std::to_string(Minute) + ":" +
				(Second < 10 ? "0" : "") + std::to_string(Second);
		}

		std::string ToShortString() const {
			return std::to_string(Year) + "-" +
				(Month < 10 ? "0" : "") + std::to_string(Month) + "-" +
				(Day < 10 ? "0" : "") + std::to_string(Day) + " " +
				(Hour < 10 ? "0" : "") + std::to_string(Hour) + ":" +
				(Minute < 10 ? "0" : "") + std::to_string(Minute) + ":" +
				(Second < 10 ? "0" : "") + std::to_string(Second);
		}

		std::string ToString() const {
			return std::to_string(Year) + "-" +
				(Month < 10 ? "0" : "") + std::to_string(Month) + "-" +
				(Day < 10 ? "0" : "") + std::to_string(Day) + " " +
				(Hour < 10 ? "0" : "") + std::to_string(Hour) + ":" +
				(Minute < 10 ? "0" : "") + std::to_string(Minute) + ":" +
				(Second < 10 ? "0" : "") + std::to_string(Second) + "." +
				std::to_string(Millisecond) + std::to_string(Microsecond);
		}

	private:
		std::uint32_t Year;
		std::uint32_t Month;
		std::uint32_t Day;
		std::uint32_t Hour;
		std::uint32_t Minute;
		std::uint32_t Second;
		std::uint32_t Millisecond;
		std::uint32_t Microsecond;

		DateTime(std::uint32_t y, std::uint32_t m, std::uint32_t d, std::uint32_t h, std::uint32_t minute, std::uint32_t s, std::uint32_t ms, std::uint32_t micro) :
			Year{ y }, Month{ m }, Day{ d }, Hour{ h }, Minute{ minute }, Second{ s }, Millisecond{ ms }, Microsecond{ micro } {
		}
	};
}