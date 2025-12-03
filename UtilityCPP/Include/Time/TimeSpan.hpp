#pragma once
#include <cstdint>
#include <string>

namespace BenScr {
	struct Timer;

	struct TimeSpan {
		uint16_t days = 0;
		uint8_t hours = 0;
		uint8_t minutes = 0;
		uint8_t seconds = 0;
		uint16_t milliseconds = 0;
		uint16_t microseconds = 0;

		TimeSpan(Timer timer);

		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds, int microseconds)
		{
			AddMicroseconds(microseconds);
			AddMilliseconds(milliseconds);
			AddSeconds(seconds);
			AddMinutes(minutes);
			AddHours(hours);
			AddDays(days);
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


		void SetDays(int days) {
			this->days = days;
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

		void AddDays(int days) {
			this->days += days;
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

		std::string ToShortString() const {
			return (hours < 10 ? "0" : "") + std::to_string(hours) + ":" +
				(minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
				(seconds < 10 ? "0" : "") + std::to_string(seconds);
		}

		std::string ToString() const {
			return std::to_string(days) + " days, " +
				std::to_string(hours) + " hours, " +
				std::to_string(minutes) + " minutes, " +
				std::to_string(seconds) + " seconds, " +
				std::to_string(milliseconds) + " milliseconds, " +
				std::to_string(microseconds) + " microseconds";
		}
	};
}