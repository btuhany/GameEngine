#pragma once
#include "../Core.h"
#include <random>
#include <chrono>

namespace GameEngine
{
	class ENGINE_API RandomGenerator
	{
    public:
        static int GetInt(int min, int max) {
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(GetEngine());
        }

        static float GetFloat(float min, float max) {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(GetEngine());
        }

        static double GetDouble(double min, double max) {
            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(GetEngine());
        }

        static bool GetBool() {
            std::bernoulli_distribution distribution(0.5);
            return distribution(GetEngine());
        }

    private:
        static std::mt19937& GetEngine() {
            static std::mt19937 engine(GetRandomSeed());
            return engine;
        }

        static unsigned int GetRandomSeed() {
            static std::random_device rd;
            return rd();
        }
	};
}

