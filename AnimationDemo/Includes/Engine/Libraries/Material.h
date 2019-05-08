/*----------------------------------/
/--------------Material-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_MATERIAL
#define HALE3D_MATERIAL

/* Standard include(s). */
#include <string>

/*Hale3D Includes*/
#include "../Core/Object.h"
#include "../Structs/Color4.h"
#include "../Structs/Vector3.h"
#include "../Rendering/Texture.h"

namespace Hale3D {
	class Model;
	class Shader;

	enum class BlendMode : uint8_t { //lua
		Solid,
		Alpha,
		Invalid
	};

	class Material : public Object { //lua
	public:
		Material();
		~Material();

		/* Method(s). */
		void Bind() const; //lua
		void Unbind() const; //lua

		bool HasAlpha() const; //lua
		float GetMetallic() const; //lua
		float GetRoughness() const; //lua
		float GetSpecular() const; //lua
		Shader* GetShader() const; //lua
		Color4 GetColor() const; //lua
		Vector3 GetMappingScale() const; //lua
		BlendMode GetBlendMode() const; //lua
		std::string GetPath() const; //lua
		std::string GetSurfaceProperty() const; //lua
		const std::vector<Texture*>& GetTextures() const;

		/* Static method(s). */
		static Material* Load(const std::string& pPath); //lua
		static void SetFallbackMaterial(const std::string& pPath); //lua
		static Material* GetFallbackMaterial(); //lua

	private:
		Shader* _shader;
		float _metallic;
		float _roughness;
		float _specular;
		Color4 _color;
		Vector3 _mappingScale;
		BlendMode _blendMode;
		std::string _path;
		std::string _surfaceProperty;
		std::vector<Texture*> _textures;
	};

	class MaterialArray { //lua
	public:
		void Rebuild(const Model* pModel); //lua
		void Clear(); //lua
		void Set(size_t pIndex, const std::string& pPath); //lua

		size_t Size() const; //lua
		Material* Get(size_t pIndex) const; //lua

		// Iterator support.
		std::vector<Material*>::iterator begin() { return _materials.begin(); }
		std::vector<Material*>::iterator end() { return _materials.end(); }

	private:
		std::vector<Material*> _materials;
	};
}
#endif
