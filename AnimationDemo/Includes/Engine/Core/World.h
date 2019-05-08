/*----------------------------------/
/--------------World----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_WORLD
#define HALE3D_WORLD

#include "../Structs/Matrix4.h"
#include "../Physics/PhysicsWorld.h"
#include "../BuildConfig.h"

#include <array>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

namespace Hale3D {
	class Entity;
	class Camera;

	class World { //lua
	public:
		/* Constructors & destructors. */
		World();
		~World();

		/* Update method(s). */
		virtual void Update(); //NOTE: This is the method the method users run in their App::Update() method.
		virtual void Render();

		/* Physics method(s). */
		PhysicsWorld& GetPhysicsWorld();
		const PhysicsWorld& GetPhysicsWorld() const;

		/* Entity method(s). */
		void RegisterEntity(Entity* pEntity);
		void DeregisterEntity(Entity* pEntity);
		const std::vector<Entity*>& GetEntities() const;

		/* Camera method(s). */
		void RegisterCamera(Camera* pCamera);
		void DeregisterCamera(Camera* pCamera);
		const std::vector<Camera*>& GetCameras() const;

		/* Static method(s). */
		static void SetCurrent(World* world); //lua
		static World* GetCurrent(); //lua

	private:
		/* General. */
		std::vector<Entity*> _entities;
		std::vector<Camera*> _cameras;

		/* Delta time. */
		double _lastFrameTime; // Last render time, in seconds.

		/* Physics. */
		PhysicsWorld _physicsWorld;
	};
}

#endif
