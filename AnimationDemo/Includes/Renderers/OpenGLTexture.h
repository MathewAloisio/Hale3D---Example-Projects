/*----------------------------------/
/-----------OpenGLTexture-----------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLTEXTURE
#define HALE3D_EXTERNAL_OGLTEXTURE

#include "OpenGLShader.h"

/* Hale3D include(s). */
#include "Engine/Libraries/TGAManager.h"

/* Standard include(s). */
#include <stdint.h>

namespace Hale3D {
	class Material;
	class Texture;

	struct OpenGLTexture {
		OpenGLTexture() = default;
		OpenGLTexture(Texture* pTexture);
		~OpenGLTexture();

		uint32_t m_TextureID;

		void Unbind();
		void Bind(int pIndex = -1, OpenGLShader* pShader = nullptr);
		void Allocate2D(Texture* pTexture);
		void Allocate2D(size_t pWidth, size_t pHeight, uint32_t pInternalFormat, uint32_t pPixelType, int32_t pSizedInternalFormat, const void* pPixelData);
		void Initialize2D(uint32_t pTextureID, size_t pWidth, size_t pHeight, uint32_t pFormat, uint32_t pPixelType, int32_t pInternalFormat, const void* pPixelData);
	};
}

#endif
