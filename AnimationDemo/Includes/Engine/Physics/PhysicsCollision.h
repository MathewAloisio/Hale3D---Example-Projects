/*----------------------------------/
/---------PhysicsCollision----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PHYSICSCOLLISION
#define HALE3D_PHYSICSCOLLISION

#include "../Structs/Vector3.h"

/* Standard include(s). */
#include <vector>

namespace Hale3D {
	class PhysicsCollider;

	struct PhysicsContactPoint {
		Vector3 m_Point; // The point of contact.
		Vector3 m_Normal; // The normal for this point of contact.
		Vector3 m_Distance; // The distance between the two colliders at this given contact point.
		PhysicsCollider* m_Contacter; // The collider that initiated the contact callback.
		PhysicsCollider* m_Contacted; // The collider that was contacted.
	};
	
	class PhysicsCollision {
	public:
		/* Constructor(s) & destructor(s). */
		PhysicsCollision() = default;
		PhysicsCollision(Vector3 pImpulse, Vector3 pRelativeLinearVelocity, PhysicsCollider* pCollider, const std::vector<PhysicsContactPoint>& pContactPoints);
	
		/* General. */
		const Vector3& GetImpulse() const;
		const Vector3& GetRelativeLinearVelocity() const;
		
		PhysicsCollider* GetCollider();
		const PhysicsCollider* GetCollider() const;
		
		const std::vector<PhysicsContactPoint>& GetContactPoints() const;
	
	private:
		Vector3 _impulse; // The sum of impulses applied to contact points to resolve the collision.
		Vector3 _relativeLinearVelocity; // The relative linear velocity of the collision.
		std::vector<PhysicsContactPoint> _contactPoints; // A vector of points where contact was made.
		PhysicsCollider* _collider; // The collider that was hit.
	};
}

#endif
