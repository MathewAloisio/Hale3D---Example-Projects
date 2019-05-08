/*----------------------------------/
/-------------OpenGLVBO-------------/
/-------Hale Game Engine 2017-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLVBOS
#define HALE3D_EXTERNAL_OGLVBOS
#pragma once

/*Standard Include(s)*/
#include <cstdint>

namespace Hale3D {
	class OpenGLVBO {
	public:
		OpenGLVBO();

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
		uint32_t _id;
	};

	class TextVBO : public OpenGLVBO {
	public:
		virtual void OnAllocate();
		virtual void OnDeallocate();
		virtual void OnBind();
		virtual void OnUnbind();
	};
}

#endif
