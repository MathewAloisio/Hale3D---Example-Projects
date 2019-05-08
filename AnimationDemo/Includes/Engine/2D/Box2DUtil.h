/*----------------------------------/
/-------------Box2DUtil-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BOX2DUTIL
#define HALE3D_BOX2DUTIL

#include "../Structs/Vector2.h"

/* Box2D include(s). */
#include <Box2D/Box2D.h>

namespace Hale3D {
	// Utility function(s).
	Vector2 Vector2FromBox2D(const b2Vec2& pVector);
	b2Vec2 Vector2ToBox2D(const Vector2& pVector);
}

#endif
