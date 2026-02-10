#pragma once
#include  <chrono>
#include <sstream>

namespace BenScr {
	class Timer {
		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock>;
		using Duration = std::chrono::duration<double>;

	public:
		Timer() :
			m_Start{ Clock::now() },
			m_PausedDuration{ Duration::zero() },
			m_IsPaused{ false } {
			m_Start = Clock::now();
		}

		void Continue() {
			if (m_IsPaused) {
				m_Start = Clock::now();
				m_IsPaused = false;
			}
		}

		void Pause() {
			if (!m_IsPaused) {
				m_PausedDuration += Clock::now() - m_Start;
				m_IsPaused = true;
			}
		}

		const double GetTotalElapsedSeconds() const  {
			return GetTotalElapsedAs<std::chrono::seconds>();
		}
		const double GetTotalElapsedMilliseconds() const {
			return GetTotalElapsedAs<std::chrono::milliseconds>();
		}

		template<typename Period>
		const std::enable_if_t<
			std::chrono::treat_as_floating_point_v<typename Duration::rep> ||
			std::is_arithmetic_v<typename Duration::rep>,
			double
		> GetTotalElapsedAs() const {
			return std::chrono::duration_cast<Period>(GetTotalElapsedTime()).count();
		}

		const bool IsPaused() const { return m_IsPaused; }
	private:
		TimePoint m_Start;
		Duration m_PausedDuration;
		bool m_IsPaused;

		const Duration GetTotalElapsedTime() const {
			if (m_IsPaused) {
				return m_PausedDuration;
			}
			else {
				return m_PausedDuration + (Clock::now() - m_Start);
			}
		}
	};

	inline std::ostream& operator<<(std::ostream& os,const Timer& timer) {
		return os << timer.GetTotalElapsedMilliseconds() << " ms";;
	}
}