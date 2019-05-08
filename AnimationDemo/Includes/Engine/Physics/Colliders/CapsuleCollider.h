/*----------------------------------/
/----------CapsuleCollider----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLLIDERS_CAPSULECOLLIDER
#define HALE3D_COLLIDERS_CAPSULECOLLIDER

#include "../PhysicsCollider.h"
#include "../../Structs/AABB.h"

namespace Hale3D {
	class CapsuleCollider : public PhysicsCollider {
	public:
		/* Constructor(s) & destructor(s). */
		CapsuleCollider(const AABB& pAABB);
		~CapsuleCollider();
	};
}

#endif
