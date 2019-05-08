/*----------------------------------/
/------------OpenGLSkybox-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLSKYBOX
#define HALE3D_EXTERNAL_OGLSKYBOX

#include "OpenGLVertexBuffer.h"

/* Hale3D include(s). */
#include "Engine/Rendering/Skybox.h"

/* Standard include(s). */
#include <array>

namespace Hale3D {
	class Camera;

	/* OpenGLSkyboxBuffer. */
	class OpenGLSkyboxBuffer : public OpenGLVertexBuffer {
	public:
		virtual void OnAllocate();
		virtual void OnDeallocate();
		virtual void OnBind();
	};

	/* OpenGLSkybox. */
	class OpenGLSkybox {
	public:
		/* Constructor(s) & destructor(s). */
		OpenGLSkybox();
		~OpenGLSkybox();

		/* General. */
		void Draw(Camera* pCamera);
		OpenGLSkyboxBuffer& GetBuffer();

		/* Static constant member(s). */
		static const std::array<Vector3, 36> VERTEX_POSITIONS;

	protected:
		OpenGLSkyboxBuffer _buffer;
	};
}

#endif
