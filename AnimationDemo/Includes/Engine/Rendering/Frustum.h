/*----------------------------------/
/-------------Frustum---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/

#ifndef HALE3D_RENDERING_FRUSTRUM
#define HALE3D_RENDERING_FRUSTRUM

#include "../Structs/AABB.h"
#include "../Structs/Plane.h"
#include "../Structs/EnumerateArray.h"

namespace Hale3D {
	struct Matrix4;

	enum class FrustumPlane : uint8_t {
		Left,
		Right,
		Top,
		Bottom,
		Near,
		Far
	};

	/*Frustum*/
	class Frustum {
	public:
		/* Method(s). */
		void Update(const Matrix4& pMatrix);
		bool CheckSphere(const Vector3& pSphereCenter, float pSphereRadius) const;

	private:
		EnumerateArray<FrustumPlane, Plane, 6> _planes;
	};
}

#endif
