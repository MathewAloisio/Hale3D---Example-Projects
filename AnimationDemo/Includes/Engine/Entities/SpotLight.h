/*----------------------------------/
/-----------SpotLight--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_SPOTLIGHT
#define HALE3D_SPOTLIGHT

/*Hale3D Includes*/
#include "../Core/Entity.h"

namespace Hale3D {
	class SpotLight : public Entity { //lua
	public:
		DECLARE_ENTITY_CLASS(SpotLight) //lua

		/* Constructor(s) & destructor(s). */
		SpotLight();
		virtual ~SpotLight();
	};
}

#endif
