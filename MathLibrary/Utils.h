#pragma once

#include <cmath>

#include "DriscollMathUtils.h"

namespace Driscoll
{
	/* Maximum tolerance for comparing floats
	 *
	 * @details Equivalent to "1.e-4f". Read as "1 times 10 to the power of -4".
	 */
	constexpr float MAX_FLOAT_DELTA = 0.0003f;
	/* The former is a constant equivalent to Unreal Engine's default threshold.
	 *
	 * We can ensure this is applicable to our environment by using a
	 * static_assert, which is checked at compile time.
	 */
	static_assert((3.e-4f) == MAX_FLOAT_DELTA);

	/* Constant for Pi
 *
 * @details Prefer C++ STDLIB (see https://en.cppreference.com/w/cpp/numeric/constants)
 */
	[[deprecated]]
	constexpr float Pi = 3.14159265358979323846264338327950288f;

	// Deg2Rad
	constexpr float Rad2Deg = Pi / 180.0f;

	// Rad2Deg
	constexpr float Deg2Rad = 1.0f / Rad2Deg;

	template<typename T>
	inline T ApproximatelyEquals(const T& a, const T& b, const T& Threshold = MAX_FLOAT_DELTA)
	{
		return std::abs(a - b) < Threshold;
	}

	inline float AngleFrom2D(float x, float y)
	{
		return atan2(y, x);
	}

	inline float AngleFrom2DDeg(float x, float y)
	{
		return atan2(y, x) * Rad2Deg;
	}

	inline float AngleFrom2DVec(Vector2D vec)
	{
		AngleFrom2D(vec.x, vec.y);
	}

	inline float AngleFrom2DDegVec(Vector2D vec)
	{
		AngleFrom2DDeg(vec.x, vec.y);
	}

	template<typename T, typename A>
	T Lerp(const T& Start, const T& End, const A& Alpha)
	{
		T Dist = End - Start;
		return Start + Dist * Alpha;
	}

	template<typename T>
	inline T CosDeg(T _x)
	{
		return cos(_x * Rad2Deg);
	}

	template<typename T>
	inline T SinDeg (T _x)
	{
				return sin(_x * Rad2Deg);
	}
}