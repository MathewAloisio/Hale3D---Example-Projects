/*----------------------------------/
/------------BoxCollider------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLLIDERS_BOXCOLLIDER
#define HALE3D_COLLIDERS_BOXCOLLIDER

#include "../PhysicsCollider.h"
#include "../../Structs/AABB.h"

namespace Hale3D {
	class BoxCollider : public PhysicsCollider {
	public:
		/* Constructor(s) & destructor(s). */
		BoxCollider(const AABB& pAABB);
		~BoxCollider();
	};
}

#endif
