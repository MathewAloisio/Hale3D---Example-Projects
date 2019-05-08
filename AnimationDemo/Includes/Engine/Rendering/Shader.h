/*----------------------------------/
/--------------Shader---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_BASESHADER
#define HALE3D_BASESHADER

/* Hale3D include(s). */
#include "../Core/Object.h"
#include "../Structs/ReferenceTable.h"

/* Standard include(s). */
#include <string>

namespace Hale3D {
	class Shader : public Object {
	public:
		/* Methods. */
		std::string GetPath() const;

		virtual void Remove();

		/* Static methods. */
		static Shader* Load(const std::string& pPath);

		/* Static - debug Mode. */
		static void SetDebugMode(bool pDebug);
		static bool GetDebugMode();

	private:
		std::string _path;

		/* Reference counting. */
		static ReferenceTable<Shader*> _shaderReference;
	};
}

#endif
