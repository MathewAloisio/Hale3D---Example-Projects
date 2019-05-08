/*----------------------------------/
/-------------Vector4---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_VECTOR4
#define HALE3D_VECTOR4
#include <string>

namespace Hale3D {
	struct Vector4 { //lua
		/* Constructor(s) & destructor(s). */
		Vector4(); //lua
		Vector4(const Vector4& other); //lua
		Vector4(const float pX, const float pY, const float pZ, const float pW); //lua
		Vector4(Vector4&& pMovable);

		/* Member(s). */
		union { float x, r; };
		union { float y, g; };
		union { float z, b; };
		union { float w, a; };
		//float x, y, z, w, r, g, b, a; //lua

		/* Operator overload(s). */
		bool operator==(const Vector4& other) const; //lua
		bool operator!=(const Vector4& other) const;
		Vector4& operator=(const Vector4& other);
		Vector4& operator=(Vector4&& pMovable);
		Vector4 operator+(const Vector4& other) const; //lua
		Vector4 operator+(const float units) const; //lua
		Vector4 operator-(const Vector4& other) const; //lua
		Vector4 operator-(const float units) const; //lua
		Vector4 operator*(const Vector4& other) const; //lua
		Vector4 operator*(const float units) const; //lua
		Vector4 operator/(const Vector4& other) const; //lua
		Vector4 operator/(const float units) const; //lua
		void operator+=(const Vector4& other);
		void operator+=(const float units);
		void operator-=(const Vector4& other);
		void operator-=(const float units);
		void operator*=(const Vector4& other);
		void operator*=(const float units);
		void operator/=(const Vector4& other);
		void operator/=(const float units);

		/* Methods. */
		float Length() const; //lua
		float Max() const; //lua
		float Dot(const Vector4& other) const; //lua
		Vector4 Normalize() const; //lua
		Vector4 Lerp(const Vector4& other, float lerpFactor) const; //lua
		Vector4 Absolute() const; //lua

		std::string ToString() const; //lua

		/* Static member(s). */
		static const Vector4 ZERO; //lua
	};
}

namespace std {
	template <> struct hash<Hale3D::Vector4> {
		size_t operator()(const Hale3D::Vector4& obj) const {
			return size_t((hash<float>()(obj.x * 73856093) ^ hash<float>()(obj.y * 19349669) ^ hash<float>()(obj.z * 83492791) ^ hash<float>()(obj.w * 50331653) << 1) >> 1);
		}
	};
}

#endif
