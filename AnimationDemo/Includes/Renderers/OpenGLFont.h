/*----------------------------------/
/------------OpenGLFont-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLFONT
#define HALE3D_EXTERNAL_OGLFONT

#include "Engine/Rendering/Font.h"

/* Standard include(s). */
#include <vector>
#include <unordered_map>

namespace Hale3D {
	class Font;

	class OpenGLShader;
	class OpenGLFont {
	public:
		OpenGLFont(Font* pFont);
		~OpenGLFont();

		void BindAtlasTexture(uint32_t pIndex, OpenGLShader* pShader = nullptr);
		void OnAllocateGlyph(char32_t pGlyphIndex, const Glyph& pGlyph, const uint8_t* pBuffer);

	private:
		Font* _font;
		uint32_t _atlasTexture;
	};
}

#endif
