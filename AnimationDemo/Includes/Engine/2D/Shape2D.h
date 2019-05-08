/*----------------------------------/
/--------------Shape2D--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_SHAPE2D
#define HALE3D_SHAPE2D

/* Box2D include(s). */
#include <Box2D/Box2D.h>

namespace Hale3D {
	class Shape2D { //lua
	public:
		/* Drawing method(s). */
		virtual void Draw() const {}; //lua
	};
}

#endif
