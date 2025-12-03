#pragma once
#include <chrono>

namespace BenScr {
	struct TimeSpan {
		uint32_t years = 0;
		uint16_t days = 0;
		uint8_t hours = 0;
		uint8_t minutes = 0;
		uint8_t seconds = 0;
		uint16_t milliseconds = 0;
		uint16_t microseconds = 0;

		TimeSpan(int years, int days, int hours, int minutes, int seconds, int milliseconds, int microseconds)
		{
			AddMicroseconds(microseconds);
			AddMilliseconds(milliseconds);
			AddSeconds(seconds);
			AddMinutes(minutes);
			AddHours(hours);
			AddDays(days);
			AddYears(years);
		}
		TimeSpan(int hours, int minutes, int seconds) {
			AddSeconds(seconds);
			AddMinutes(minutes);
			AddHours(hours);
		}
		TimeSpan(int days, int hours, int minutes, int seconds) {
			AddSeconds(seconds);
			AddMinutes(minutes);
			AddHours(hours);
			AddDays(days);
		}
		
		void SetYears(int years) {
			this->years = years;
		}
		void SetDays(int days) {
			this->days = days % 365;
			int totalYears = days / 365;
			this->years += totalYears;
		}
		void SetHours(int hours) {
			this->hours = hours % 24;
			int totalDays = hours / 24;
			AddDays(totalDays);
		}
		void SetMinutes(int minutes) {
			this->minutes = minutes % 60;
			int totalHours = minutes / 60;
			AddHours(totalHours);
		}
		void SetSeconds(int seconds) {
			this->seconds = seconds % 60;
			int totalMinutes = seconds / 60;
			AddMinutes(totalMinutes);
		}
		void SetMilliseconds(int milliseconds) {
			this->milliseconds = milliseconds % 1000;
			int totalSeconds = milliseconds / 1000;
			AddSeconds(totalSeconds);
		}
		void SetMicroseconds(int microseconds) {
			this->microseconds = microseconds % 1000;
			int totalMilliseconds = microseconds / 1000;
			AddMilliseconds(totalMilliseconds);
		}

		void AddYears(int years) {
			this->years += years;
		}
		void AddDays(int days) {
			this->days = days % 365;
			int totalYears = days / 365;
			this->years += totalYears;
		}
		void AddHours(int hours) {
			this->hours += hours % 24;
			int totalDays = hours / 24;
			AddDays(totalDays);
		}
		void AddMinutes(int minutes) {
			this->minutes += minutes % 60;
			int totalHours = minutes / 60;
			SetHours(totalHours);
		}
		void AddSeconds(int seconds) {
			this->seconds += seconds % 60;
			int totalMinutes = seconds / 60;
			SetMinutes(totalMinutes);
		}
		void AddMilliseconds(int milliseconds) {
			this->milliseconds += milliseconds % 1000;
			int totalSeconds = milliseconds / 1000;
			SetSeconds(totalSeconds);
		}
		void AddMicroseconds(int microseconds) {
			this->microseconds += microseconds % 1000;
			int totalMilliseconds = microseconds / 1000;
			AddMilliseconds(totalMilliseconds);
		}

		explicit TimeSpan(std::chrono::steady_clock::time_point timePoint) {
			auto endPoint = std::chrono::steady_clock::now();

			auto totalMicroseconds =
				std::chrono::duration_cast<std::chrono::microseconds>(
					endPoint - timePoint
				).count();

			microseconds = totalMicroseconds % 1000;
			totalMicroseconds /= 1000;

			milliseconds = totalMicroseconds % 1000;
			totalMicroseconds /= 1000;

			seconds = totalMicroseconds % 60;
			totalMicroseconds /= 60;

			minutes = totalMicroseconds % 60;
			totalMicroseconds /= 60;

			hours = totalMicroseconds % 24;
			totalMicroseconds /= 24;

			days = static_cast<int>(totalMicroseconds);
		}

		std::string ToString() const {
			return std::to_string(years) + " years, " +
				std::to_string(days) + " days, " +
				std::to_string(hours) + " hours, " +
				std::to_string(minutes) + " minutes, " +
				std::to_string(seconds) + " seconds, " +
				std::to_string(milliseconds) + " milliseconds, " +
				std::to_string(microseconds) + " microseconds";
		}
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
	};

	class Timer {
	public:

		Timer() : m_StartPoint{ std::chrono::high_resolution_clock::now() } {}

		void Reset() {
			m_StartPoint = std::chrono::high_resolution_clock::now();
		}

		int ElapsedMilliseconds() {
			auto endPoint = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - m_StartPoint).count();
		}
		int ElapsedMicroseconds() {
			auto endPoint = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds>(endPoint - m_StartPoint).count();
		}
		int ElapsedSeconds() {
			auto endPoint = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::seconds>(endPoint - m_StartPoint).count();
		}

	private:
		std::chrono::steady_clock::time_point m_StartPoint;
	};
}