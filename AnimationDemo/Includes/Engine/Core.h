/*----------------------------------/
/-----------Engine Core-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CORE
#define HALE3D_CORE

#include <string>

namespace Hale3D {
	namespace Core {
		/* Method(s). */
		void Start(int pArgC, const char* pArgs[], bool pEnableUI = true);
		void Stop();

		void Update();
		bool IsStarted();

		/*Callbacks*/
		void OnExit();
	}
}

#endif
