/*----------------------------------/
/-----------OpenGLCubemap-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLCUBEMAP
#define HALE3D_EXTERNAL_OGLCUBEMAP

/* Hale3D include(s). */
#include "Engine/Rendering/Cubemap.h"
#include "Engine/Libraries/TGAManager.h"

/* Standard include(s). */
#include <stdint.h>

namespace Hale3D {
	class OpenGLShader;
	struct OpenGLCubemap {
		/* Constructor(s) & destructor(s). */
		OpenGLCubemap(Cubemap* pCubemap, CubemapFaceArray& pCubeFaces);
		~OpenGLCubemap();

		uint32_t m_TextureID;

		void Unbind();
		void Bind(int pIndex = -1, OpenGLShader* pShader = nullptr);
	};
}

#endif
