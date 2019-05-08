/*----------------------------------/
/-------------Object----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
/* A base-object for game-engine components to inherit from. */
#ifndef HALE3D_OBJECT
#define HALE3D_OBJECT

/* Standard include(s). */
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

namespace Hale3D {
	/* Underlying Object class for Hale3D objects. */
	class Object { //lua
	public:
		virtual ~Object() = default;

		/* Lifecycle management. */
		virtual void Remove(); //lua

		/* Generic data. */
		void SetData(void* pData);
		void SetRenderData(void* pData);
		template <typename T> T GetData() {
			return static_cast<T>(_data.m_User);
		}
		template <typename T> T GetRenderData() {
			return static_cast<T>(_data.m_Render);
		}

	private:
		struct {
			void* m_User; // User defined data.
			void* m_Render; // Data pointer for renderer implementations.
		} _data;
	};
}

#endif
