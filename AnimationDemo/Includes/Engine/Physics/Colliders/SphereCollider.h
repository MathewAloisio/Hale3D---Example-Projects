/*----------------------------------/
/-----------SphereCollider----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLLIDERS_SPHERECOLLIDER
#define HALE3D_COLLIDERS_SPHERECOLLIDER

#include "../PhysicsCollider.h"

namespace Hale3D {
	class SphereCollider : public PhysicsCollider {
	public:
		/* Constructor(s) & destructor(s). */
		SphereCollider(const AABB& pAABB);
		~SphereCollider();
	};
}

#endif
