#pragma once
#include <cstdint>
#include <chrono>

namespace BenScr {
	class Random {
	public:
		Random() {
			SetRandomized();
		}
		Random(uint64_t seed) : state(seed) {}

		// Info: Sets the internal state to a randomized value
		void SetRandomized() {
			auto t = (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::steady_clock::now().time_since_epoch()).count();
			auto s = (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()).count();

			uint64_t m = mem_entropy();
			state = mix64(t ^ s ^ m);
		}

		template <class T>
		std::enable_if_t<std::is_integral_v<T>, T>
			Next() {
			using U = std::make_unsigned_t<T>;
			U u = (U)NextU64();
			return (T)u;
		}


		template <class T>
		std::enable_if_t<std::is_integral_v<T>, T>
			Next(T max) {
			if constexpr (std::is_signed_v<T>) {
				if (max <= 0) throw std::invalid_argument("max must be > 0");
			}
			else {
				if (max == 0) throw std::invalid_argument("max must be > 0");
			}
			return Next((T)0, max);
		}

		template<class T>
		std::enable_if_t<std::is_floating_point_v<T>, T>
			Next(T min, T max) {
			if (!(min < max)) throw std::invalid_argument("min < max required");
			T u = Uniform01<T>();
			return min + (max - min) * u;
		}

		template <class T>
		std::enable_if_t<std::is_integral_v<T>, T>
			Next(T min, T max) {
			if (!(min < max)) throw std::invalid_argument("min must be < max");

			using U = std::make_unsigned_t<std::common_type_t<T, uint64_t>>;

			auto span_signed = (std::common_type_t<int64_t, T>)(max) - (std::common_type_t<int64_t, T>)(min);
			U span = (U)span_signed;

			U r = UniformBelow(span);
			return (T)((std::common_type_t<T, U>)min + (std::common_type_t<T, U>)r);
		}

	private:
		template <class U>
		U UniformBelow(U bound) {
			static_assert(std::is_unsigned_v<U>);
			if (bound == 0) throw std::invalid_argument("bound must be > 0");

			U lim = std::numeric_limits<U>::max() - (std::numeric_limits<U>::max() % bound);
			U x;
			do {
				x = (U)NextU64();
			} while (x >= lim);
			return x % bound;
		}
		template<class T>
		T Uniform01() {
			static_assert(std::is_floating_point_v<T>);
			constexpr int bits = 53;

			uint64_t r = NextU64();
			uint64_t v = r >> (64 - bits);
			return (T)v * (T)(1.0 / (1ULL << bits));
		}

		uint64_t NextU64() {
			state ^= state >> 12;
			state ^= state << 25;
			state ^= state >> 27;
			return state * 2685821657736338717ULL;
		}

		static inline uint64_t mix64(uint64_t x) {
			x ^= x >> 30; x *= 0xbf58476d1ce4e5b9ULL;
			x ^= x >> 27; x *= 0x94d049bb133111ebULL;
			x ^= x >> 31;
			return x;
		}

		static inline uint64_t mem_entropy() {
			uint64_t stack_addr = 0;
			uint64_t heap_addr = reinterpret_cast<uint64_t>(new int(123));
			delete reinterpret_cast<int*>(heap_addr);

			uint64_t fn_addr = reinterpret_cast<uint64_t>(&mem_entropy);
			stack_addr = reinterpret_cast<uint64_t>(&stack_addr);

			return mix64(stack_addr ^ (heap_addr << 1) ^ (fn_addr << 2));
		}

		uint64_t state;
	};
}