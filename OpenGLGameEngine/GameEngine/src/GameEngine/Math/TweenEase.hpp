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

        // Back easing
        static float EaseInBack(float t, float s = 1.70158f) {
            return t * t * ((s + 1) * t - s);
        }

        static float EaseOutBack(float t, float s = 1.70158f) {
            t -= 1;
            return t * t * ((s + 1) * t + s) + 1;
        }

        static float EaseInOutBack(float t, float s = 1.70158f) {
            s *= 1.525f;
            if (t < 0.5f) return 0.5f * (t * t * ((s + 1) * t - s));
            float p = t - 1;
            return 0.5f * (p * p * ((s + 1) * p + s) + 2);
        }

        // Back easing
        static float EaseInElastic(float t) {
            const float c4 = (2 * M_PI) / 3;
            return (t == 0) ? 0 : (t == 1) ? 1 : -std::pow(2, 10 * (t - 1)) * std::sin((t - 1 - 0.1f) * c4);
        }

        static float EaseOutElastic(float t) {
            const float c4 = (2 * M_PI) / 3;
            return (t == 0) ? 0 : (t == 1) ? 1 : std::pow(2, -10 * t) * std::sin((t - 0.1f) * c4) + 1;
        }

        static float EaseInOutElastic(float t) {
            const float c5 = (2 * M_PI) / 4.5f;
            if (t == 0) return 0;
            if (t == 1) return 1;
            if (t < 0.5f) return -0.5f * std::pow(2, 20 * t - 10) * std::sin((20 * t - 11.125f) * c5);
            return std::pow(2, -20 * t + 10) * std::sin((20 * t - 11.125f) * c5) * 0.5f + 1;
        }
    };
}
