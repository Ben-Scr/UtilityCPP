#include "../../Include/Time/Timer.hpp"
#include "../../Include/Time/TimeSpan.hpp"

namespace BenScr {
    std::string Timer::ToString() {
        TimeSpan elapsed(*this);
        return elapsed.ToShortString();
    }
}