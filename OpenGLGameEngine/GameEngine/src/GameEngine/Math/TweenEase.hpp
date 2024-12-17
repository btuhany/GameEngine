#pragma once
#include <cmath>
#include <corecrt_math_defines.h>

namespace GameEngine
{
    class TweenEase {
    public:
        // Linear easing
        static float Linear(float t) {
            return t;
        }

        // Quadratic easing
        static float EaseInQuad(float t) {
            return t * t;
        }

        static float EaseOutQuad(float t) {
            return t * (2 - t);
        }

        static float EaseInOutQuad(float t) {
            if (t < 0.5f) return 2 * t * t;
            return -1 + (4 - 2 * t) * t;
        }

        // Cubic easing
        static float EaseInCubic(float t) {
            return t * t * t;
        }

        static float EaseOutCubic(float t) {
            float p = t - 1;
            return p * p * p + 1;
        }

        static float EaseInOutCubic(float t) {
            if (t < 0.5f) return 4 * t * t * t;
            float p = t - 1;
            return (p * p * p * 4) + 1;
        }

        // Sinusoidal easing
        static float EaseInSine(float t) {
            return 1 - std::cos((t * M_PI) / 2);
        }

        static float EaseOutSine(float t) {
            return std::sin((t * M_PI) / 2);
        }

        static float EaseInOutSine(float t) {
            return -0.5f * (std::cos(M_PI * t) - 1);
        }

        // Exponential easing
        static float EaseInExpo(float t) {
            return (t == 0) ? 0 : std::pow(2, 10 * (t - 1));
        }

        static float EaseOutExpo(float t) {
            return (t == 1) ? 1 : 1 - std::pow(2, -10 * t);
        }

        static float EaseInOutExpo(float t) {
            if (t == 0) return 0;
            if (t == 1) return 1;
            if (t < 0.5f) return 0.5f * std::pow(2, 10 * (2 * t - 1));
            return 0.5f * (2 - std::pow(2, -10 * (2 * t - 1)));
        }
    };
}
