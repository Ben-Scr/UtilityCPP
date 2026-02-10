#pragma once
#include <chrono>
#include <string>

namespace BenScr {
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

		std::string ToString();
	private:
		std::chrono::steady_clock::time_point m_StartPoint;
	};
}