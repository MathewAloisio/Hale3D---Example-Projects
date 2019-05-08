/*----------------------------------/
/--------------Math-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_MATH
#define HALE3D_MATH

/* Preprocessor directive(s). */
#define CHECK_BIT(pVariable, pPos) ((pVariable) & (1 << pPos))

#include "Util.h"
#include "../Structs/Vector2.h"
#include "../Structs/EnumerateArray.h"

/* Standard include(s). */
#include <cmath>
#include <algorithm>

namespace Hale3D {
	enum class RectanglePoint : int8_t { //lua
		None = -1,
		UpperLeft = 0,
		UpperRight = 1,
		LowerRight = 2,
		LowerLeft = 3
	};
	typedef EnumerateArray<RectanglePoint, Vector2, 4> RectanglePoints;
	typedef EnumerateArray<RectanglePoint, float, 4> RectangleRadiuses;

	enum class RectangleBound : uint8_t { //lua
		Left = 0,
		Right = 1,
		Bottom = 2,
		Top = 3
	};
	typedef EnumerateArray<RectangleBound, float, 4> RectangleBounds;

	namespace Math {
		/* Constant variables. */
		const long double PI_LONG_DOUBLE = 3.141592653589793238L;
		const double PI_DOUBLE = 3.141592653589793;
		const float PI = 3.1415927f;
		const float EPSILON = 0.00001f;

		/* Methods. */
		float Lerp(float pA, float pB, float pF); //lua
		float ToRadians(const float pAngle); //lua
		float ToDegrees(const float pRadians); //lua
		float Abs(const float pValue); //lua
		bool IsWhole(const float pValue); //lua
		bool IsPowerOfTwo(const int pValue); //lua

		// Bounds checking (points calculated).
		bool IsPointInCircle(const Vector2& pPoint, const Vector2& pCircleCenter, float pCircleRadius); //lua
		bool IsPointInRectangle(const Vector2& pPoint, const Vector2& pUpperLeft, const Vector2& pLowerRight); //lua

		bool IsPointOnCircleEdge(const Vector2& pPoint, const Vector2& pCircleCenter, float pCircleRadius, float pThreshold = 1.f); //lua

		RectanglePoint GetPointCornerOnRectangle(const Vector2& pPoint, const Vector2& pUpperLeft, const Vector2& pLowerRight, float pThreshold = 1.f); //lua
		bool IsPointOnRectangleCorner(const Vector2& pPoint, const Vector2& pUpperLeft, const Vector2& pLowerRight, float pThreshold = 1.f); //lua

		Vector2 GetRectangleCornerPoint(RectanglePoint pRectPoint, const Vector2& pUpperLeft, const Vector2& pLowerRight); //lua
		RectanglePoints GetRectangleCornerPoints(const Vector2& pUpperLeft, const Vector2& pLowerRight);

		RectangleBounds GetRectangleBounds(const Vector2& pUpperLeft, const Vector2& pLowerRight);

		// Rectangle bounds checking (points supplied).
		bool IsPointInRectangleBounds(const Vector2& pPoint, const RectangleBounds& pRectBounds);

		RectanglePoint GetPointCornerOnRectangle(const Vector2& pPoint, const RectanglePoints& pRectCorners, float pThreshold = 1.f);
		bool IsPointOnRectangleCorner(const Vector2& pPoint, const RectanglePoints& pRectCorners, float pThreshold = 1.f);

		/*Numeric Template Methods*/
		template<typename T>
		typename std::enable_if<std::is_integral<T>::value, T>::type CountFactors(T pNumber) {
			/*Principle: All numbers have at least 2 factors.*/
			int factorCount = 2;
			for (T i = 2, max = T(std::sqrt(pNumber)); i < max; ++i) {
				if ((pNumber % i) == 0) {
					++factorCount;
				}
			}
			return factorCount;
		}

		template<typename T, typename = typename std::enable_if<std::is_integral<T>::value, T>::type>
		bool IsPrime(T pNumber) {
			/*Principle: Any even number that's not 2 is NOT prime.*/
			if (pNumber == 2) {
				return true;
			}
			else if ((pNumber % 2) == 0) { return false; }

			/*Principle: Negative numbers are not prime.*/
			if (pNumber < 0) return false;

			/*Principle: All numbers have at least 2 factors, if we find a 3rd it's NOT prime.*/
			/*Principle: We only have to check up to the square root of the number for factors, 
						 past that they will NEVER be factors.*/
			/*Principle: Start loop at 3 because all numbers are divisible by one, excludes one. We explicity check 2 above, exclude 2.*/
			for (T i = 3, max = std::sqrt(pNumber); i < max; ++i) {
				if ((pNumber % i) == 0) {
					return false;
				}
			}
			return true;
		}

		template<typename T>
		typename std::enable_if<std::is_integral<T>::value, T>::type FindNextPrime(T pNumber) {
			if (IsPrime(pNumber)) return pNumber;
			for (T i = pNumber, i < static_cast<T>(2 * pNumber); ++i) {
				if (IsPrime(i)) {
					return i;
				}
			}
		}

		/*Arithmetic methods.*/
		template<typename T>
		typename std::enable_if<std::is_arithmetic<T>::value, T>::type Clamp(const T& pValue, const T& pMin, const T& pMax) {
			return std::max(pMin, std::min(pValue, pMax));
		}
	}
}

#endif
