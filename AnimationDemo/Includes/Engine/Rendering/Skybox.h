/*----------------------------------/
/--------------Skybox---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_SKYBOX
#define HALE3D_SKYBOX

/* Hale3D includes. */
#include "Cubemap.h"
#include "Renderer.h"
#include "Shader.h"
#include "../Core/Object.h"
#include "../Structs/ReferenceTable.h"
#include "../Libraries/TGAManager.h"

namespace Hale3D {
	/* Skybox. */
	class Skybox : public Object { //lua
	public:
		/* Constructor(s) & destructor(s). */
		Skybox() = default;
		Skybox(const std::string& pPath);
		virtual ~Skybox();

		virtual void Remove();

		/* General. */
		Shader* GetShader() const;
		Cubemap* GetCubemap() const;
		const std::string& GetPath() const;

		/* Fallback shader. */
		static void SetFallbackShader(const std::string& pPath);
		static Shader* GetFallbackShader();

		/* Static method(s). */
		static ExpandingBuffer CreateBuffer(const CubemapFaceArray& pCubeFaces);
		static Skybox* Create(CubemapFaceArray& pCubeFaces);
		static Skybox* Load(const std::string& pPath);

		/* Static constant members. */
		static constexpr uint32_t UniqueIdentifier = ('B' << 24) + ('Y' << 16) + ('K' << 8) + 'S'; // Used to confirm that a file contains an engine-supported skybox.
		static constexpr uint32_t CurrentVersion = 1;

	private:
		Skybox(const std::string& pPath, TGAOrigin pImageOrigin);
		std::string _path;
		Cubemap* _cubemap;
		Shader* _shader;

		/* Reference counting. */
		static ReferenceTable<Skybox*> _skyboxReference;
	};
}
#endif
