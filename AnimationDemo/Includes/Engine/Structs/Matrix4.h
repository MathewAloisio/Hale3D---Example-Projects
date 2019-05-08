/*----------------------------------/
/-------------Matrix4---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_MATRIX4
#define HALE3D_MATRIX4
#include "Vector3.h"
#include "Vector4.h"

namespace Hale3D {
	struct Vector3;
	struct Vector4;

	struct Matrix4 { //lua
		Matrix4(); //lua
		Matrix4(float pSource[16]);
		Matrix4(float pM00, float pM01, float pM02, float pM03,
			float pM10, float pM11, float pM12, float pM13,
			float pM20, float pM21, float pM22, float pM23,
			float pM30, float pM31, float pM32, float pM33
		);
		Matrix4(const Matrix4& pOther) = default; //lua
		Matrix4(Matrix4&& pMovable);

		/*Operators*/
		Matrix4& operator=(const Matrix4& pOther) = default;
		Matrix4& operator=(Matrix4&& pMovable);

		Matrix4 operator+(const Matrix4& pOther) const; //lua
		Matrix4 operator-(const Matrix4& pOther) const; //lua
		Matrix4& operator+=(const Matrix4& pOther);
		Matrix4& operator-=(const Matrix4& pOther);
		Matrix4 operator*(const Matrix4& pOther) const; //lua
		Matrix4& operator*=(const Matrix4& pOther);
		bool operator==(const Matrix4& pOther) const; //lua
		bool operator!=(const Matrix4& pOther) const;
		float operator[](int pIndex) const;
		float& operator[](int pIndex);

		/*General Methods*/
		void Set(float pSource[16]);
		void Set(float pM00, float pM01, float pM02, float pM03,
			float pM10, float pM11, float pM12, float pM13,
			float pM20, float pM21, float pM22, float pM23,
			float pM30, float pM31, float pM32, float pM33
		);
		void SetRow(int pIndex, const float pRow[4]);
		void SetRow(int pIndex, const Vector4& pVec); //lua
		void SetRow(int pIndex, const Vector3& pVec); //lua
		void SetColumn(int pIndex, const float pCol[4]);
		void SetColumn(int pIndex, const Vector4& pVec); //lua
		void SetColumn(int pIndex, const Vector3& pVec); //lua
		Matrix4 Perspective(float pL, float pR, float pB, float pT, float pN, float pF); //lua
		Matrix4 Perspective(float pFovY, float pAspect, float pNear, float pFar); //lua
		Matrix4 Orthographic(float pL, float pR, float pB, float pT, float pN, float pF); //lua

		float& Get(const int pColumn, const int pRow); //lua
		const float& Get(const int pColumn, const int pRow) const;

		/*Initializizers & Manipulators*/
		float GetCofactor(float pM0, float pM1, float pM2, float pM3, float pM4, float pM5, float pM6, float pM7, float pM8) const; //lua
		float GetDeterminant() const; //lua
		Matrix4 Inverse(); //lua
		Matrix4& Identity(); //lua
		Matrix4& Transpose(); //lua
		Matrix4& Invert(); //lua
		Matrix4& InvertEuclidean(); //lua
		Matrix4& InvertAffine(); //lua
		Matrix4& InvertGeneric(); //lua

		/*Transformations*/
		Matrix4& Translate(const float pX, const float pY, const float pZ); //lua
		Matrix4& Translate(const Vector3& pValue); //lua
		Matrix4& Rotate(const Vector3& pAxis, float pAngle = 1.0f); //lua
		Matrix4& Scale(const float pScale); //lua
		Matrix4& Scale(const Vector3& pScale); //lua
		Matrix4& LookAt(float pX, float pY, float pZ); //lua
		Matrix4& LookAt(float pX, float pY, float pZ, float uX, float uY, float uZ); //lua
		Matrix4& LookAt(const Vector3& pTarget); //lua
		Matrix4& LookAt(const Vector3& pTarget, const Vector3& pUp); //lua

		Vector3 GetAngles() const; //lua
		Vector3 GetTranslation() const; //lua

		/* Member(s). */
		float m[16];
	};
}

#endif
