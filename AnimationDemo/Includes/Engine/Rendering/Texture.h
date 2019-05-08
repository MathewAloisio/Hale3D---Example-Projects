/*----------------------------------/
/-------------Texture---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TEXTURE
#define HALE3D_TEXTURE

/* Standard includes. */
#include <string>
#include <vector>
#include <array>
#include <cstdint>

/* Hale3D includes. */
#include "BaseTexture.h"
#include "../Core/Object.h"
#include "../Libraries/TGAManager.h"
#include "../Structs/ReferenceTable.h"

namespace Hale3D {
	class Material;

	class Texture : public BaseTexture { //lua
	public:
		virtual void Remove();

		/* Texture methods. */
		std::string GetPath() const; //lua
		std::string GetName() const; //lua

		TGAManager& GetImage();
		const TGAManager& GetImage() const;

		/* Static methods. */
		static Texture* Load(const std::string& pPath); //lua
		static void SetFallbackTexture(const std::string& pPath); //lua
		static Texture* GetFallbackTexture(); //lua

	private:
		Texture(const std::string& pPath);

		TGAManager _image;
		std::string _path;
		std::string _name;

		/* Reference counting. */
		static ReferenceTable<Texture*> _textureReference;
	};
}
#endif
