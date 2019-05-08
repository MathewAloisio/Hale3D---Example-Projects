/*----------------------------------/
/------------NewtonWorld------------/
/-------Hale Game Engine 2018-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_NEWTONWORLD
#define HALE3D_EXTERNAL_NEWTONWORLD

#include "Engine/Physics/PhysicsWorld.h"

namespace Hale3D {
	class NewtonWorld : public PhysicsWorld {
	public:
		/* General callback(s). */
		virtual void OnUpdate();
		virtual void OnInitialize();
		virtual void OnDeinitialize();

	private:
	};
}

#endif
