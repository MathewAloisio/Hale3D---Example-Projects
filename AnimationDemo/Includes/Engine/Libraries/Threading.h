/*----------------------------------/
/------------Threading--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_THREADING
#define HALE3D_THREADING
#include "../BuildConfig.h"
#include "../Structs/ThreadPool.h"

namespace Hale3D {
	namespace Threading {
		/* Master thread pool. */
		ThreadPool& GetPool();

		/* Concurrency information. */
		uint32_t GetUnreservedThreadCount();
	}
}

#endif
