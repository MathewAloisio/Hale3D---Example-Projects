/*----------------------------------/
/--------------World2D--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_WORLD2D
#define HALE3D_WORLD2D

#include "Box2DUtil.h"

namespace Hale3D {
	class World2D { //lua
	public:
		/* Constructor(s) & destructor(s). */
		World2D(const Vector2& pGravity = Vector2(0.0f, -9.81f), int pTickrate = 60); //lua

		/* General. */
		void Update();

		/* Tickrate, precision & performance control. */
		void SetTickrate(int pTickrate); //lua
		int GetTickrate() const; //lua

		void SetVelocityIterations(int pIterations); //lua
		int GetVelocityIterations() const; //lua

		void SetPositionIterations(int pIterations); //lua
		int GetPositionIterations() const; //lua

		/* Pausing & unpausing. */
		void SetPaused(bool pPaused); //lua
		bool IsPaused() const; //lua

		/* Global state. */
		static World2D* GetCurrent(); //lua
		static void SetCurrent(World2D* pWorld2D); //lua

		/* Static constant(s). */
		static constexpr int DEFAULT_VELOCITY_ITERATIONS = 8; //lua
		static constexpr int DEFAULT_POSITION_ITERATIONS = 3; //lua

	private:
		bool _paused;
		int _tickrate;
		int _velocityIterations;
		int _positionIterations;
		float _timeStep;
		b2World _box2DWorld;
	};
}

#endif
