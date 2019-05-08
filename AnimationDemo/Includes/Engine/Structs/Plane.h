/*----------------------------------/
/--------------Plane----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PLANE
#define HALE3D_PLANE

#include "Vector3.h"

namespace Hale3D {
	struct Plane { //lua
		/* Constructor(s) & destructor(s). */
		Plane() = default; //lua
		Plane(const Plane& pOther) = default; //lua
		Plane(Plane&& pMovable) = default;

		/* Member(s). */
		float d;
		Vector3 normal;

		/* Method(s). */
		float Distance(const Vector3& pPoint) const;
		void SetCoefficients(Vector3 pNormal, float pD);
		void SetNormalAndPoint(const Vector3& pNormal, const Vector3& pPoint);

		std::string ToString() const; //lua
	};
}

#endif
