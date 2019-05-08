/*----------------------------------/
/-------------Cubemap---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CUBEMAP
#define HALE3D_CUBEMAP

/* Hale3D include(s). */
#include "../Core/Object.h"
#include "../Libraries/TGAManager.h"
#include "../Structs/EnumerateArray.h"

/* Standard include(s). */
#include <array>

namespace Hale3D {
	enum class CubeFace : uint8_t {
		Right,
		Left,
		Top,
		Bottom,
		Front,
		Back
	};
	typedef EnumerateArray<CubeFace, TGAManager, 6> CubemapFaceArray;
	typedef EnumerateArray<CubeFace, std::string, 6> CubemapFacePathArray;

	class Cubemap : public Object { //lua
	public:
		/* Constructor(s) & destructor(s). */
		Cubemap(CubemapFaceArray& pCubeFaces);
		Cubemap(const CubemapFacePathArray& pCubeFacePaths);
		virtual ~Cubemap();
	};
}
#endif
