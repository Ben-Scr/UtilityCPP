#pragma once
#include <cstdint>

namespace BenScr {
	struct TimeOnly {
	   uint8_t hour = 0;
	   uint8_t minute = 0;
	   uint8_t second = 0;
	   uint16_t millisecond = 0;
	   uint16_t microsecond = 0;
   };
}