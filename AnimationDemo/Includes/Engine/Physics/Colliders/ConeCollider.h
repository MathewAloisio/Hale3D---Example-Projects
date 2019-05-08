/*----------------------------------/
/-----------ConeCollider------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLLIDERS_CONECOLLIDER
#define HALE3D_COLLIDERS_CONECOLLIDER

#include "../PhysicsCollider.h"
#include "../../Structs/AABB.h"

namespace Hale3D {
	class ConeCollider : public PhysicsCollider {
	public:
		/* Constructor(s) & destructor(s). */
		ConeCollider(const AABB& pAABB);
		~ConeCollider();
	};
}

#endif
