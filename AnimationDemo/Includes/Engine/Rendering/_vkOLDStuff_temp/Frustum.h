/*----------------------------------/
/------------Frustum---------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/

#ifndef HALE3D_RENDERING_FRUSTRUM
#define HALE3D_RENDERING_FRUSTRUM
#pragma once

#include <array>
#include "../Structs/Vector3.h"
#include "../Structs/Vector4.h"

namespace Hale3D {
	struct Matrix4;
	
	/*Frustum*/
	class Frustum {
	public:
		/*Methods*/
		void Update(Matrix4& pMatrix);
		bool CheckSphere(Vector3 pPosition, float pRadius);
		
		/*Members*/
		const enum side { LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3, BACK = 4, FRONT = 5 };
		std::array<Vector4, 6> planes;	
	};
}

#endif
