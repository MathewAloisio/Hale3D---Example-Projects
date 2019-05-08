/*----------------------------------/
/---------------Font----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BASEFONT
#define HALE3D_BASEFONT

/*Hale3D Include(s)*/
#include "../Core/Object.h"
#include "../Structs/Vector2.h"
//#include "../Structs/Matrix3.h" //TODO
#include "../Structs/ReferenceTable.h"

/* Standard include(s). */
#include <string>
#include <unordered_map>

/*Include FreeType*/
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H

namespace Hale3D {
	struct FT_Instance {
		bool m_Enabled;
		FT_Library m_Instance;
	};
	
	struct GlyphVec {
		GlyphVec();
		GlyphVec(const uint16_t pX, const uint16_t pY);
		GlyphVec(GlyphVec&& pMovable);

		GlyphVec& operator=(const GlyphVec& pOther);

		union { uint16_t x, width; };
		union { uint16_t y, height; };
	};

	struct Glyph { // Cache friendly Glyph structure.
		Glyph();
		Glyph(const GlyphVec& pAdvance, const GlyphVec& pOffset, const GlyphVec& pDimensions, const Vector2& pAtlasOffset); //lua
		Glyph(Glyph&& pMovable);

		bool IsRenderable() const;

		GlyphVec m_Advance;
		GlyphVec m_Offset;
		GlyphVec m_Dimensions;
		Vector2 m_AtlasOffset;
	};

	typedef std::vector<Glyph> GlyphCollection;

	class Font : public Object { //lua
	public:
		/* Constructor(s) & destuctor(s). */
		Font();

		/* Methods. */
		const std::string& GetPath() const; //lua
		uint32_t GetAtlasWidth() const; //lua
		uint32_t GetAtlasHeight() const; //lua
		const GlyphCollection& GetGlyphs() const;

		virtual void Remove();

		/* Static methods. */
		static void InitializeFonts();
		static void DeinitializeFonts();
		static Font* Load(const std::string& pPath, int32_t pPixelHeight); //lua

		static const uint32_t MAX_ATLAS_WIDTH;

		/* Static members. */
		static FT_Instance FreeType;

	private:
		int16_t _pixelHeight;
		std::string _path;
		GlyphCollection _glyphs;

		struct {
			uint32_t m_Width;
			uint32_t m_Height;
		} _atlas;

		/* Reference counting. */
		static ReferenceTable<Font*> _fontReference;
	};
}

#endif
