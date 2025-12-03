#include "../../Include/Time/TimeSpan.hpp"
#include "../../Include/Time/Timer.hpp"

namespace BenScr {
	TimeSpan::TimeSpan(Timer timer) {
		AddMicroseconds(timer.ElapsedMicroseconds());
	}
}