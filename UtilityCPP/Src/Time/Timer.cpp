#include "../../Include/Time/Timer.hpp"
#include "../../Include/Time/TimeSpan.hpp"

namespace BenScr {
	std::string Timer::ToString() {
		return TimeSpan(0, 0, 0).ToShortString();
	}
}