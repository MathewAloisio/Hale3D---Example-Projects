/*----------------------------------/
/-------------Vector3---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_VECTOR3
#define HALE3D_VECTOR3
#include <string>

namespace Hale3D {
	struct Matrix4;
	struct Quaternion;

	struct Vector3 { //lua
		/* Constrctors & destructors. */
		Vector3(); //lua
		Vector3(const Vector3& other); //lua
		Vector3(const float pX, const float pY, const float pZ); //lua
		Vector3(Vector3&& pMovable);

		/* Member(s). */
		// NOTE: The engines euler angles rotate clock-wise around the positive end of the direction vectors.
		//       Angle     x = -up/+down pitch.
		//		 Angle     y = -left/+right yaw.
		//       Angle     z = -"left roll"/+"right roll".
		union { float x, r, pitch; }; // x - pitch. (Based on Vector3::LEFT.)
		union { float y, g, yaw; }; // y - yaw. (Based on Vector3::UP.)
		union { float z, b, roll; };  // z - roll. (Based on Vector3::FORWARD.)
		//float x, y, z, r, g, b, pitch, yaw, roll; //lua

		/* Operator overloads. */
		bool operator==(const Vector3& other) const; //lua
		bool operator!=(const Vector3& other) const;
		Vector3& operator=(const Vector3& other);
		Vector3& operator=(Vector3&& pMovable);
		Vector3 operator+(const Vector3& other) const; //lua
		Vector3 operator+(const float units) const; //lua
		Vector3 operator-(const Vector3& other) const; //lua
		Vector3 operator-(const float units) const; //lua
		Vector3 operator*(const Vector3& other) const; //lua
		Vector3 operator*(const float units) const; //lua
		Vector3 operator/(const Vector3& other) const; //lua
		Vector3 operator/(const float units) const; //lua
		void operator+=(const Vector3& other);
		void operator+=(const float units);
		void operator-=(const Vector3& other);
		void operator-=(const float units);
		void operator*=(const Vector3& other);
		void operator*=(const float units);
		void operator/=(const Vector3& other);
		void operator/=(const float units);

		/* Methods. */
		float Length() const; //lua
		float Max() const; //lua
		float Min() const; //lua
		float Dot(const Vector3& other) const; //lua
		float Distance(const Vector3& pValue) const; //lua
		Vector3 Cross(const Vector3& other) const; //lua
		Vector3 Normalize() const; //lua
		Vector3 Lerp(const Vector3& other, float lerpFactor) const; //lua
		Vector3 Rotate(const Vector3& other, const float angle) const; //lua
		Vector3 Rotate(const Quaternion& pRotation) const; //lua
		Vector3 Absolute() const; //lua
		Vector3 Perpendicular() const; //lua
		Vector3 Transform(const Matrix4& pMatrix) const; //lua

		std::string ToString() const; //lua

		/* Static member(s). */
		static const Vector3 FORWARD; //lua
		static const Vector3 BACKWARD; //lua
		static const Vector3 RIGHT; //lua
		static const Vector3 LEFT; //lua
		static const Vector3 UP; //lua
		static const Vector3 DOWN; //lua

		static const Vector3 ZERO; //lua

		/* Static method(s). */
		static Vector3 FromRotationMatrix(const Matrix4& pRotationMatrix); //lua
	};
}

namespace std {
	template <> struct hash<Hale3D::Vector3> {
		size_t operator()(const Hale3D::Vector3& obj) const {
			return size_t((hash<float>()(obj.x * 73856093) ^ hash<float>()(obj.y * 19349669) ^ hash<float>()(obj.z * 83492791) << 1) >> 1);
		}
	};
}

#endif
