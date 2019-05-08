/*----------------------------------/
/--------------Time-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TIME
#define HALE3D_TIME

/* Standard include(s). */
#include <string>
#include <stdint.h>

namespace Hale3D {
	namespace Time {
		void __Update(); //NOTE: For internal use by the engine ONLY!

		/*Deltas & compensation (Time it takes to execute frame/physics simulation.)*/
		/*
			Function name: GetTimeFactor
			Function return:		double - If 'GetFPS() == GetTargetFPS()' returns 1 | If 'GetFPS() == (GetTargetFPS() * 2)' returns 0.5 | If 'GetFPS() == (GetTargetFPS() / 2)' returns 2.0
			Function description:	Returns 'Time::GetDelta() / (1000.f / GetTargetFPS()). Intended to be used for multiplying changing values to compensate for frame delay.
				
		*/
		double GetFPS(); //lua
		double GetTimeFactor(); //lua
		double GetDelta(); //lua
		double GetFixedDelta(); //lua
		
		/* Time Method(s). */
		void __SetEpoch(); //NOTE: For internal use by the engine ONLY!
		void __SetAppTime(); //NOTE: For internal use by the engine ONLY!
		double GetCurrent(); //lua
		double Milliseconds(); //lua
		std::string GetDateAndTime(); //lua

		void Pause(); //lua
		void Resume(); //lua
		bool IsPaused(); //lua

		/* FPS Method(s). */
		void SetTargetFPS(int pTarget); //lua
		double GetTargetFPS(); //lua
	}
}

#endif
