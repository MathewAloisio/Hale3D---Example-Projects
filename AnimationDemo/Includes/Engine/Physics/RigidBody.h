/*----------------------------------/
/-------------RigidBody-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_RIGIDBODY
#define HALE3D_RIGIDBODY

#include "PhysicsCollision.h"
#include "PhysicsCollider.h"
#include "../Core/Object.h"
#include "../Structs/Vector3.h"

/* Bullet include(s). */
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>

namespace Hale3D {
	class RigidBody : public Object {
	public:
		/* Constructor(s) & destructor(s). */
		RigidBody(CollisionShape* pCollisionShape, float pMass, float pStaticFriction = 0.5f, float pDynamicFriction = 0, float pCOR = 0); // pCOR => Coefficient of restitution.
		virtual ~RigidBody();

		/* General. */
		void SetGravityEnabled(bool pEnabled);
		bool IsGravityEnabled() const;

		void SetPhysicsEnabled(bool pEnabled);
		bool IsPhysicsEnabled() const;

		void SetCollisionsEnabled(bool pEnabled);
		bool IsCollisionsEnabled() const;

		void SetMass(float pMass);
		float GetMass() const;

		void SetAngularDrag(float pAngularDrag);
		float GetAngularDrag() const;

		void SetMaxAngularVelocity(float pMaxAngularVelocity);
		float GetMaxAngularVelocity() const;

		void SetAngularVelocity(const Vector3& pAngularVelocity);
		Vector3 GetAngularVelocity() const;

		void SetCenterOfMass(const Vector3& pCenter);
		Vector3 GetCenterOfMass() const;

		/* General callback(s). */
		virtual void OnCollisionStart(const PhysicsCollision& pCollisionInfo) {};	// Called when a collision event is triggered by this rigid body's collider.
		virtual void OnCollisionRepeat(const PhysicsCollision& pCollisionInfo) {};	// Called each frame that the collision event is repeated by this rigid body's collider.
		virtual void OnCollisionStop(const PhysicsCollision& pCollisionInfo) {};	// Called when a collision event is ended by this rigid body's collider.

	protected:
		bool _gravityEnabled; // Should gravity influence this rigid body? true = yes / false = no.
		bool _physicsEnabled; // Should the physics worlds have an effect on this rigid body? true = yes / false = no.
		bool _collisionsEnabled; // Should this rigid body detect collisions? true = yes / false = no.
		float _mass; // The mass of the rigid body.
		float _angularDrag; // Angular drag of the rigid body.
		float _maxAngularVelocity; // The maximum angular velocity in radians/second.
		Vector3 _angularVelocity; // Angular velocity of the rigid body in radians/second.
		Vector3 _centerOfMass; // Center of mass for the rigid body.

		/* Bullet physics. */
		btRigidBody* _rigidBody;
		btMotionState* _motionState;
		CollisionShape* _collisionShape;
	};
}

#endif
