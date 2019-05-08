/*----------------------------------/
/-------------Vector2---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_VECTOR2
#define HALE3D_VECTOR2
#include <string>

namespace Hale3D {
	struct Vector2 { //lua
		/* Constructor(s) & destructor(s). */
		Vector2(); //lua
		Vector2(const Vector2& other); //lua
		Vector2(const float pX, const float pY); //lua
		Vector2(Vector2&& pMovable);

		/* Member(s). */
		union { float x, r, width; };
		union { float y, g, height; };
		//float x, y, r, g, width, height; //lua

		/* Operator overload(s). */
		bool operator==(const Vector2& other) const; //lua
		bool operator!=(const Vector2& other) const;
		Vector2& operator=(const Vector2& other);
		Vector2& operator=(Vector2&& pMovable);
		Vector2 operator+(const Vector2& other) const; //lua
		Vector2 operator+(const float units) const; //lua
		Vector2 operator-(const Vector2& other) const; //lua
		Vector2 operator-(const float units) const; //lua
		Vector2 operator*(const Vector2& other) const; //lua
		Vector2 operator*(const float units) const; //lua
		Vector2 operator/(const Vector2& other) const; //lua
		Vector2 operator/(const float units) const; //lua
		void operator+=(const Vector2& other); 
		void operator+=(const float units);
		void operator-=(const Vector2& other);
		void operator-=(const float units);
		void operator*=(const Vector2& other);
		void operator*=(const float units);
		void operator/=(const Vector2& other);
		void operator/=(const float units);

		/* Method(s). */
		float Length() const; //lua
		float Max() const; //lua
		float Dot(const Vector2& other) const; //lua
		float Cross(const Vector2& other) const; //lua
		float Distance(const Vector2& pValue) const; //lua
		Vector2 Normalize() const; //lua
		Vector2 Lerp(const Vector2& other, float lerpFactor) const; //lua 
		Vector2 Rotate(const float pRotation) const; //lua
		Vector2 Absolute() const; //lua
		Vector2 Perpendicular() const; //lua
		Vector2 Round() const; //lua

		std::string ToString() const; //lua

		/* Static member(s). */
		static const Vector2 ZERO; //lua
	};
}

namespace std {
	template <> struct hash<Hale3D::Vector2> {
		size_t operator()(const Hale3D::Vector2& obj) const {
			return size_t((hash<float>()(obj.x * 73856093) ^ hash<float>()(obj.y * 83492791) << 1) >> 1);
		}
	};
}

#endif
