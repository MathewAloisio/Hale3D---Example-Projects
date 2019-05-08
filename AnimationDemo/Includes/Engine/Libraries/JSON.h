/*----------------------------------/
/--------------JSON-----------------/
/-------Hale Game Engine 2019-------/
/----------------------------------*/

// Uses https://github.com/nlohmann/json.

#ifndef HALE3D_JSON
#define HALE3D_JSON

/* Third party include(s). */
#include <nlohmann/json.hpp>

namespace Hale3D {
	// JSON - proxy for nlohmann's json object.
	using JSON = nlohmann::json;
}

#endif
