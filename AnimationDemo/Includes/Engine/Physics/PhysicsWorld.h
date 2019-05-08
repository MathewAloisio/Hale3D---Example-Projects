/*----------------------------------/
/-----------PhysicsWorld------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PHYSICSWORLD
#define HALE3D_PHYSICSWORLD

/* Standard include(s). */
#include <stdint.h>

#include "../Structs/Matrix4.h"
#include "../Structs/Quaternion.h"

/* Bullet include(s). */
#include <bullet/btBulletDynamicsCommon.h>

namespace Hale3D {
	class World;

	// Utility function(s).
	Vector3 Vector3FromBullet(const btVector3& pVector);
	Vector4 Vector4FromBullet(const btVector4& pVector);

	btVector3 Vector3ToBullet(const Vector3& pVector);
	btVector4 Vector4ToBullet(const Vector4& pVector);

	Quaternion QuaternionFromBullet(const btQuaternion& pQuaternion);

	btQuaternion QuaternionToBullet(const Quaternion& pQuaternion);

	// PhysicsWorld.
	class PhysicsWorld {
	public:
		/* Constructor(s) & destructor(s). */
		PhysicsWorld(World* pWorld);
		~PhysicsWorld();

		/* General. */
		void Update();

		void SetGravity(const Vector3& pGravity);
		Vector3 GetGravity() const;

		void SetTargetUPS(uint16_t pTargetUPS);
		uint16_t GetTargetUPS();

		World* GetWorld();

		/* Static constant variable(s). */
		static const Vector3 DEFAULT_GRAVITY;

	protected:
		double _lastFrameTime;
		double _currentFrameTime;

		btBroadphaseInterface* _broadphase;
		btCollisionDispatcher* _collisionDispatcher;
		btDefaultCollisionConfiguration* _collisionConfig;
		btSequentialImpulseConstraintSolver* _solver;
		btDiscreteDynamicsWorld* _bulletWorld;

		uint16_t _targetUPS;
		World* _world;
	};
}

#endif
