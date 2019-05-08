/*----------------------------------/
/-----OpenGLShaderStorageBuffer-----/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGL_SHADERSTORAGEBUFFER
#define HALE3D_EXTERNAL_OGL_SHADERSTORAGEBUFFER

/*Standard Include(s)*/
#include <cstdint>

namespace Hale3D {
	class OpenGLShaderStorageBuffer {
	public:
		void Allocate();
		void Deallocate();
		void Bind();
		void Unbind();

		bool IsAllocated() const;
		uint32_t GetID() const;

		virtual void OnAllocate() {};
		virtual void OnDeallocate() {};
		virtual void OnBind() {};
		virtual void OnUnbind() {};

	private:
		uint32_t _bufferID;
	};
}

#endif
