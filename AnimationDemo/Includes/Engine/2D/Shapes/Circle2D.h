/*----------------------------------/
/-------------Circle2D--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CIRCLE2D
#define HALE3D_CIRCLE2D

#include "../Shape2D.h"

namespace Hale3D {
	class Circle2D : public Shape2D { //lua
	public:
		Circle2D(float pRadius);

		/* Drawing method(s). */
		virtual void Draw() const {}; //lua

		/* Transformation setting(s). */
		float GetRadius() const; //lua
		void SetRadius(float pRadius); //lua

	protected:
		b2CircleShape _shape;
	};
}

#endif
