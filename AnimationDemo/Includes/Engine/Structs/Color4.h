/*----------------------------------/
/--------------Color4---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLOR4
#define HALE3D_COLOR4
#include <string>

#include "Vector4.h"

namespace Hale3D {
	struct Vector4;

	struct Color4 { //lua
		/* Constructor(s) & destructor(s). */
		Color4(); //lua
		Color4(const Color4& pColor) = default; //lua
		Color4(Color4&& pMovable) = default;
		Color4(const Vector4& pVector); //lua
		Color4(const uint8_t pR, const uint8_t pG, const uint8_t pB, const uint8_t pA); //lua

		/* Conversion. */
		operator Vector4() const {
			return Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
		}

		/* Member(s). */
		uint8_t r; //lua
		uint8_t g; //lua
		uint8_t b; //lua
		uint8_t a; //lua

		/* Operator overload(s). */
		Color4& operator=(const Color4& pColor) = default;
		Color4& operator=(Color4&& pMovable) = default;

		bool operator==(const Color4& other) const; //lua
		bool operator!=(const Color4& other) const;
		Color4 operator+(const Color4& other) const; //lua
		Color4 operator+(const uint8_t units) const; //lua
		Color4 operator-(const Color4& other) const; //lua
		Color4 operator-(const uint8_t units) const; //lua
		Color4 operator*(const Color4& other) const; //lua
		Color4 operator*(const uint8_t units) const; //lua
		Color4 operator*(const float units) const; //lua
		Color4 operator/(const Color4& other) const; //lua
		Color4 operator/(const uint8_t units) const; //lua
		Color4 operator/(const float units) const; //lua
		void operator+=(const Color4& other); 
		void operator+=(const uint8_t units);
		void operator-=(const Color4& other);
		void operator-=(const uint8_t units);
		void operator*=(const Color4& other);
		void operator*=(const uint8_t units);
		void operator*=(const float units);
		void operator/=(const Color4& other);
		void operator/=(const uint8_t units);
		void operator/=(const float units);

		/* Method(s). */
		Color4 Lerp(const Color4& pOther, float pLerpFactor) const; //lua
		std::string ToString() const; //lua
	};
}

namespace std {
	template <> struct hash<Hale3D::Color4> {
		size_t operator()(const Hale3D::Color4& obj) const {
			return size_t((hash<uint8_t>()(obj.r * 73856093) ^ hash<uint8_t>()(obj.g * 19349669) ^ hash<uint8_t>()(obj.b * 83492791) ^ hash<uint8_t>()(obj.a * 402653189) << 1) >> 1);
		}
	};
}

#endif
