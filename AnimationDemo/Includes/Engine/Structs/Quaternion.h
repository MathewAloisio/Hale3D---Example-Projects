/*----------------------------------/
/-----------Quaternion--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_QUATERNION
#define HALE3D_QUATERNION
#include "Matrix4.h"
#include "Vector3.h"

#include <string>

namespace Hale3D {
	struct Vector3;
	struct Matrix4;

	struct Quaternion { //lua
		/* Constructors & destructor(s). */
		Quaternion(); //lua
		Quaternion(const Matrix4& pMatrix); //lua
		Quaternion(const Quaternion& pOther) = default; //lua
		Quaternion(Quaternion&& pMovable) = default;
		Quaternion(const Vector3& pOther, const float pAngle = 1.0f); //lua
		Quaternion(const float pX, const float pY, const float pZ, const float pW); //lua

		/* Members. */
		float x; //lua
		float y; //lua
		float z; //lua
		float w; //lua

		/* Methods. */
		float Length() const; //lua
		float Dot(const Quaternion& pOther) const; //lua
		Quaternion NLerp(const Quaternion& pOther, const float pLerpFactor, bool pShortest) const; //lua
		Quaternion SLerp(const Quaternion& pOther, const float pLerpFactor, bool pShortest, const float pThreshold = 0.005f) const; //lua
		Quaternion Normalize() const; //lua
		Quaternion Inverse() const; //lua Conjugate quaternion.
		Quaternion& ComputeUnitW(); //lua Computes the 'w' component of a unit Quaternion. ('w' is between 0.f and 1.f)
		float GetNormal() const; //lua
		Vector3 GetAngles() const; //lua
		Vector3 GetUp() const; //lua
		Vector3 GetDown() const; //lua
		Vector3 GetForward() const; //lua
		Vector3 GetBackward() const; //lua
		Vector3 GetRight() const; //lua
		Vector3 GetLeft() const; //lua
		Matrix4 GetRotationMatrix() const; //lua
		void SetAngles(const Vector3& pAngles); //lua

		std::string ToString() const;

		/* Operator overloads. */
		bool operator==(const Quaternion& pOther) const; //lua
		bool operator!=(const Quaternion& pOther) const;

		Quaternion& operator=(const Quaternion& pOther) = default;
		Quaternion& operator=(Quaternion&& pMovable) = default;
		Quaternion& operator+=(const float pUnits);
		Quaternion& operator+=(const Quaternion& pOther);
		Quaternion& operator-=(const float pUnits);
		Quaternion& operator-=(const Quaternion& pOther);
		Quaternion& operator*=(const float pUnits);
		Quaternion& operator*=(const Vector3& pValue);
		Quaternion& operator*=(const Quaternion& pOther);
		Quaternion& operator/=(const Quaternion& pOther);
		Quaternion& operator/=(const float pScalar);
		
		Quaternion operator+(const float pUnits) const; //lua
		Quaternion operator+(const Quaternion& pOther) const; //lua
		Quaternion operator-(const float pUnits) const; //lua
		Quaternion operator-(const Quaternion& pOther) const; //lua
		Quaternion operator*(const float pUnits) const; //lua
		Quaternion operator*(const Vector3& pValue) const; //lua
		Quaternion operator*(const Quaternion& pOther) const; //lua
		Quaternion operator/(const Quaternion& pOther) const; //lua
		Quaternion operator/(const float pScalar) const; //lua
	};
}

#endif
