#pragma once
#include <cstdint>
#include <string>
#include "Timer.hpp"

namespace BenScr {

	struct TimeSpan {
		uint16_t Days = 0;
		uint8_t Hours = 0;
		uint8_t Minutes = 0;
		uint8_t Seconds = 0;
		uint16_t Milliseconds = 0;
		uint16_t Microseconds = 0;

		explicit  TimeSpan(Timer timer);

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
			this->Days = days;
		}
		void SetHours(int hours) {
			this->Hours = hours % 24;
			int totalDays = hours / 24;
			AddDays(totalDays);
		}
		void SetMinutes(int minutes) {
			this->Minutes = minutes % 60;
			int totalHours = minutes / 60;
			AddHours(totalHours);
		}
		void SetSeconds(int seconds) {
			this->Seconds = seconds % 60;
			int totalMinutes = seconds / 60;
			AddMinutes(totalMinutes);
		}
		void SetMilliseconds(int milliseconds) {
			this->Milliseconds = milliseconds % 1000;
			int totalSeconds = milliseconds / 1000;
			AddSeconds(totalSeconds);
		}
		void SetMicroseconds(int microseconds) {
			this->Microseconds = microseconds % 1000;
			int totalMilliseconds = microseconds / 1000;
			AddMilliseconds(totalMilliseconds);
		}

		void AddDays(int days) {
			this->Days += days;
		}
		void AddHours(int hours) {
			this->Hours += hours % 24;
			int totalDays = hours / 24;
			AddDays(totalDays);
		}
		void AddMinutes(int minutes) {
			this->Minutes += minutes % 60;
			int totalHours = minutes / 60;
			SetHours(totalHours);
		}
		void AddSeconds(int seconds) {
			this->Seconds += seconds % 60;
			int totalMinutes = seconds / 60;
			SetMinutes(totalMinutes);
		}
		void AddMilliseconds(int milliseconds) {
			this->Milliseconds += milliseconds % 1000;
			int totalSeconds = milliseconds / 1000;
			SetSeconds(totalSeconds);
		}
		void AddMicroseconds(int microseconds) {
			this->Microseconds += microseconds % 1000;
			int totalMilliseconds = microseconds / 1000;
			AddMilliseconds(totalMilliseconds);
		}

		std::string ToShortString() const {
			return (Hours < 10 ? "0" : "") + std::to_string(Hours) + ":" +
				(Minutes < 10 ? "0" : "") + std::to_string(Minutes) + ":" +
				(Seconds < 10 ? "0" : "") + std::to_string(Seconds);
		}

		std::string ToString() const {
			return std::to_string(Days) + " days, " +
				std::to_string(Hours) + " hours, " +
				std::to_string(Minutes) + " minutes, " +
				std::to_string(Seconds) + " seconds, " +
				std::to_string(Milliseconds) + " milliseconds, " +
				std::to_string(Microseconds) + " microseconds";
		}
	};
}