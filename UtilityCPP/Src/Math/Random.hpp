#pragma once
#include <cstdint>
#include <random>
#include <chrono>

namespace BenScr {
    class Random {
    public:
        Random() = delete;

        static bool NextBool();

        static std::uint8_t NextByte();
        static std::uint8_t NextByte(std::uint8_t min, std::uint8_t max);
        static std::uint8_t NextByte(std::uint8_t max);

        static float NextFloat();
        static float NextFloat(float max);
        static float NextFloat(float min, float max);

        static double NextDouble();
        static double NextDouble(double max);
        static double NextDouble(double min, double max);

        static int NextInt32();
        static  int NextInt32(int max);
        static int NextInt32(int min, int max);

        static void SetSeed(uint32_t seed) { s_Gen.seed(seed); }

    private:
        inline static std::mt19937 s_Gen{ std::random_device{}() };
    };
}