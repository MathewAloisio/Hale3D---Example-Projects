/*----------------------------------/
/------------Transform--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TRANSFORM
#define HALE3D_TRANSFORM
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <vector>

namespace Hale3D {
	class Transform { //lua
	public:
		/* Constructor(s) & destructor(s). */
		Transform(); //lua

		/* Method(s). */
		void Rotate(const Vector3& axis, const float angle); //lua
		void LookRotation(const Vector3& point, const Vector3& up); //lua
		void SetScale(const Vector3& pScale); //lua
		void SetPosition(const Vector3& pPosition); //lua
		void SetAngles(const Vector3& pAngles); //lua
		void SetRotation(const Quaternion& pOrientation); //lua
		void SetParent(Transform* pParent = nullptr); //lua
		Vector3 GetScale() const; //lua
		Vector3 GetPosition() const; //lua
		Vector3 GetAngles() const; //lua
		Quaternion GetRotation() const; //lua
		Quaternion GetLookRotation(const Vector3& point, const Vector3& up); //lua
		Matrix4 GetMatrix() const; //lua
		Transform* GetParent(); //lua
		std::vector<Transform*>& GetChildren();

	private:
		struct {
			Matrix4 m_Translation;
			Matrix4 m_Scalar;
		} _matrices;

		Vector3 _position;
		Vector3 _scale;
		Quaternion _rotation;
		Transform* _parent = nullptr;
		std::vector<Transform*> _children;
	};
}

#endif
