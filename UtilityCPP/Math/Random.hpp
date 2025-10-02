#pragma once
#include <cstdint>
#include <chrono>
#include <random>
#include <thread>
#include <atomic>


namespace UtilityCPP {
	class Random {
	public:
		Random() {
			SetRandomized();
		}
		Random(uint64_t seed) : state(seed) {}

		void SetRandomized() {
			using namespace std::chrono;

			auto t = static_cast<unsigned long long>(
				duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count()
				);

			std::random_device rd;
			auto g = static_cast<unsigned long long>(rd());


			auto s = static_cast<unsigned long long>(
				duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count()
				);

			state = t ^ g ^ s;
		}

		int NextState() {
			state ^= state >> 12;
			state ^= state << 25;
			state ^= state >> 27;
			return state * 2685821657736338717ULL;
		}
		int NextInt() {
		  return static_cast<int>(NextState() & 0x7FFFFFFF);
		}

	private:
		uint64_t state;
	 };
}