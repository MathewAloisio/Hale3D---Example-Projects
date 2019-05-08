/*----------------------------------/
/----------PhysicsCollider----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PHYSICSCOLLIDER
#define HALE3D_PHYSICSCOLLIDER

/* Preprocessor directive(s). */
#define PHYSSHAPE_HEADER_SIZE 6 // The size of the physics shape file header in bytes. (UniqueIdentifier and Version)

#include "PhysicsMaterial.h"
#include "PhysicsCollision.h"
#include "../Structs/AABB.h"

/* Bullet include(s). */
#include <bullet/btBulletDynamicsCommon.h>

namespace Hale3D {
	class RigidBody;

	typedef btCollisionShape CollisionShape;

	enum class PhysicsShape : uint8_t {
		None,
		Box,					// Generates a box collider.
		Capsule,				// Generates a capsule collider.
		Cone,					// Generates a cone collider.
		Cylinder,				// Generates a cylinder collider.
		Plane,					// Generates a plane collider.
		Sphere,					// Generates a sphere collider.
		ConvexHull,				// Generates a collider using the convex hull of a model.
		ConvexDecomposition,	// Generates a collider by performing convex decomposition on a model.
		Model,					// Generates a collider based on a model's vertices.
		Custom					// Tells the engine a custom physics shape has been loaded from a file, or is being manually controlled.
	};

	class PhysicsCollider {
	public:
		/* General. */
		void SetPhysicsMaterial(PhysicsMaterial pPhysicsMaterial);
		const PhysicsMaterial& GetPhysicsMaterial();
		const PhysicsMaterial& GetPhysicsMaterial() const;

		AABB GetAABB() const;

		void SetEnabled(bool pEnabled);
		bool IsEnabled();

		void SetCollisionShape(CollisionShape* pCollisionShape);
		const CollisionShape* GetCollisionShape() const;

		/* Save & load models physics shape(s). */
		bool SaveShape(const std::string& pPath, bool pOverwrite = false);
		bool LoadShape(const std::string& pPath);

		/* Static constant member(s). */
		static constexpr uint32_t UniqueIdentifier = ('S' << 24) + ('Y' << 16) + ('H' << 8) + 'P'; // Used to confirm that a file contains engine-supported physics shapes.
		static constexpr uint16_t CurrentVersion = 1; // NOTE: CurrentVersion will change when optimizations are made to the storing of physics shapes, or in the event the engine ever changes physics engines.

		/* General callback(s). */
		virtual void OnCollisionStart(const PhysicsCollision& pCollisionInfo) {};	// Called when a collision event is triggered by this collider.
		virtual void OnCollisionRepeat(const PhysicsCollision& pCollisionInfo) {};	// Called each frame that the collision event is repeated by this collider.
		virtual void OnCollisionStop(const PhysicsCollision& pCollisionInfo) {};	// Called when a collision event is ended by this collider.
		
	protected:
		/* Bullet member(s). */
		CollisionShape* _collisionShape;

	private:
		bool _enabled; // When true, collider will collide with other colliders. When false, this collider will not be involved in any collisions.
		PhysicsMaterial _physicsMaterial; // The physics material of this collider.
		RigidBody* _rigidBody; // The rigid body of this collider, or nullptr if it has no attached rigid body.
	};
}

#endif
