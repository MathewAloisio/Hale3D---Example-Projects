/*----------------------------------/
/---------OpenGLVertexBuffer--------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
/*---Encapsulates a VBO and VAO.---*/
#ifndef HALE3D_EXTERNAL_OGL_VERTEXBUFFERS
#define HALE3D_EXTERNAL_OGL_VERTEXBUFFERS

/*Standard Include(s)*/
#include <vector>
#include <cstdint>

namespace Hale3D {
	class OpenGLVertexBuffer {
	public:
		void Allocate();
		void Deallocate();
		void Bind();
		void Unbind();

		bool IsAllocated() const;
		uint32_t GetVBOID() const;
		uint32_t GetVAOID() const;

		virtual void OnAllocate() {};
		virtual void OnDeallocate() {};
		virtual void OnBind() {};
		virtual void OnUnbind() {};

	private:
		uint32_t _vboID;
		uint32_t _vaoID;
	};

	class TextBuffer : public OpenGLVertexBuffer {
	public:
		virtual void OnAllocate();
		virtual void OnDeallocate();
		virtual void OnBind();
	};

	class QuadBuffer : public OpenGLVertexBuffer {
	public:
		virtual void OnAllocate();
		virtual void OnDeallocate();
		virtual void OnBind();
	};
}

#endif
