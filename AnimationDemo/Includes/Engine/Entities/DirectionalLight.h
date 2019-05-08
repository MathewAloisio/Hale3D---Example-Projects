/*----------------------------------/
/---------DirectionalLight----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_DIRECTIONALLIGHT
#define HALE3D_DIRECTIONALLIGHT

/*Hale3D Includes*/
#include "../Core/Entity.h"

namespace Hale3D {
	class DirectionalLight : public Entity { //lua
	public:
		DECLARE_ENTITY_CLASS(DirectionalLight) //lua

		/* Constructor(s) & destructor(s). */
		DirectionalLight();
		virtual ~DirectionalLight();
	};
}

#endif
