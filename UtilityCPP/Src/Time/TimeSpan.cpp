#include "TimeSpan.hpp"
#include "Timer.hpp"

namespace BenScr {
	TimeSpan::TimeSpan(Timer timer) {
		AddMicroseconds(timer.GetTotalElapsedAs<std::chrono::microseconds>());
	}
}