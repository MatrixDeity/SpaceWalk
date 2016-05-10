#pragma once

#include <cmath>
#include <random>
#include <chrono>

//====================================================================================================

class GameMath
{
public:
	GameMath() = delete;
	GameMath(const GameMath&) = delete;
	const GameMath& operator=(const GameMath&) = delete;

	template <typename T>
	static inline T abs(T value)
	{
		return ::abs(value);
	}

	template <typename T>
	static inline T cos(T angle)
	{
		return ::cos(angle * TO_RAD);
	}

	template <typename T>
	static inline T sin(T angle)
	{
		return ::sin(angle * TO_RAD);
	}

	template <typename T>
	static inline T atan2(T y, T x)
	{
		return ::atan2(y, x) * TO_DIG;
	}

	template <typename T>
	static float computeDistance(const T& point1, const T& point2)
	{
		float dx = static_cast<float>(GameMath::abs(point1.x - point2.x));
		float dy = static_cast<float>(GameMath::abs(point1.y - point2.y));
		return ::sqrt(dx * dx + dy * dy);
	}

	template <typename T>
	static T generateRandomNumber(T min, T max)
	{
		if (min > max)
			return 0;

		return T(mGenerator() % (max - min + 1) + min);
	}

	template <typename T>
	static T generateRandomVector(const T& leftUpAngle, const T& rightDownAngle)
	{
		if (leftUpAngle.x > rightDownAngle.x || leftUpAngle.y > rightDownAngle.y)
			return T();

		return T(mGenerator() % (rightDownAngle.x - leftUpAngle.x + 1) + leftUpAngle.x, mGenerator() % (rightDownAngle.y - leftUpAngle.y + 1) + leftUpAngle.y);
	}

private:
	static const float TO_RAD;
	static const float TO_DIG;
	static std::mt19937 mGenerator;
};