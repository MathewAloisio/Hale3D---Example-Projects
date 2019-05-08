/*----------------------------------/
/---------OpenGLRenderTarget--------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLRENDERTARGET
#define HALE3D_EXTERNAL_OGLRENDERTARGET

/* OpenGLRenderer include(s). */
#include "OpenGLTexture.h"
#include "OpenGLFramebuffer.h"

namespace Hale3D {
	class OpenGLRenderTarget : public OpenGLFramebuffer {
	public:
		// Constructor(s) & destructor(s).
		OpenGLRenderTarget(uint32_t pWidth, uint32_t pHeight, bool pEnableDepth);
		~OpenGLRenderTarget();

		// Binding & unbinding.
		void Bind();
		void Unbind();

		// Member access.
		OpenGLTexture& GetTexture();

	private:
		struct {
			uint32_t width;
			uint32_t height;
		} _size;
		int _lastWriteFBO;
		uint32_t _depthBuffer;
		OpenGLTexture _texture;
	};
}

#endif
