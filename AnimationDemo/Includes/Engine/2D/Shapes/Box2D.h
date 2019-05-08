/*----------------------------------/
/--------------Box2D----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BOX2D
#define HALE3D_BOX2D

#include "../Shape2D.h"

namespace Hale3D {
	class Box2D : public Shape2D { //lua
	public:
		/* Drawing method(s). */
		virtual void Draw() const {}; //lua

	};
}

#endif
