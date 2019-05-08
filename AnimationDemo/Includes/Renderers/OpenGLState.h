/*----------------------------------/
/------------OpenGLState------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLSTATE
#define HALE3D_EXTERNAL_OGLSTATE

#include "Engine/Structs/EnumerateArray.h"

/* Standard include(s). */
#include <array>
#include <cstdint>

namespace Hale3D {
	enum class OpenGLViewportPoint : uint8_t {
		OriginX,
		OriginY,
		EndX,
		EndY
	};
	typedef EnumerateArray<OpenGLViewportPoint, uint32_t, 4> OpenGLViewport;

	namespace OpenGLState {
		/* Vertex array buffer. */
		void BindVertexArrayBuffer(uint32_t pID);
		uint32_t GetVertexArrayBuffer();

		/* Vertex element buffer. */
		void BindVertexElementBuffer(uint32_t pID);
		uint32_t GetVertexElementBuffer();

		/* Vertex array object. */
		void BindVertexArray(uint32_t pID);
		uint32_t GetVertexArray();

		/* OpenGL viewport. */
		void SetViewport(const OpenGLViewport& pViewport);
		const OpenGLViewport& GetViewport();
	}
}

#endif
