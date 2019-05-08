/*----------------------------------/
/-------------Octree----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_OCTREE
#define HALE3D_OCTREE

#include "../Structs/AABB.h"

/* Standard include(s). */
#include <array>

namespace Hale3D {
	class Octree;
	typedef std::array<Octree*, 8> OctreeNodes;

	class Octree {
	public:
		/* Bounding region. */
		const AABB& GetBoundingBox() const;

		/* Child & parent nodes. */
		Octree* GetParentNode() const;
		const OctreeNodes& GetChildNodes() const;

	private:
		/* Bounding region. */
		AABB _boundingBox;

		/* Child & parent nodes. */
		Octree* _parentNode;

		char _activeNodes; // A bitmask to track active _childNodes, only 1 comparison is required instead of 8 by using a bitmask.
		OctreeNodes _childNodes;
	};
}

#endif
