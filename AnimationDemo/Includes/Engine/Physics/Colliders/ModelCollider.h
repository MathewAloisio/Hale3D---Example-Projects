/*----------------------------------/
/-----------ModelCollider-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_COLLIDERS_MODELCOLLIDER
#define HALE3D_COLLIDERS_MODELCOLLIDER

#include "../PhysicsCollider.h"

namespace Hale3D {
	class Model;
	
	enum class ModelColliderMode : uint8_t {
		Full,					// Worst performance, highest accuracy. Model's actual vertices used to generate collision shape.
		ConvexHull,				// Best performance, lowest accuracy. Convex hull of the model.
		ConvexDecomposition		// Medium performance, high accuracy. Convex decomposition of the model.
	};
	
	class ModelCollider : public PhysicsCollider {
	public:
		/* Constructor(s) & destructor(s). */
		ModelCollider(Model* pModel, ModelColliderMode pColliderMode);
		~ModelCollider();
	};

	namespace ModelColliderShapeCache {
		struct _CacheEntry {
			Model* m_Model;
			ModelColliderMode m_ColliderMode;
			CollisionShape* m_CollisionShape;
		};

		CollisionShape* LookupModel(Model* pModel, ModelColliderMode pColliderMode); // Given a model and collider mode, returns a pointer to the corresponding cached CollisionShape, or a newly created one.
		void FreeModel(Model* pModel, ModelColliderMode pColliderMode); // Given a model and collider mode, attempts to free a cached collision shape from the list.
		void Free(); // Frees all cached collision shapes. After this is called all pointers previously obtained via LookupModel() are invalid.
	}
}

#endif
