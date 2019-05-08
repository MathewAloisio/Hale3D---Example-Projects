/*----------------------------------/
/-------------LuaHook---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_LUAHOOK
#define HALE3D_LUAHOOK

/*Hale3D Include(s)*/
#include "Interpreter.h"

/* Standard include(s). */
#include <functional>

namespace Hale3D {
	namespace LuaHook {
		void Run(const std::string& pHook, int pArgCount = 0, const std::function<void()>& pArgFunc = nullptr);
		bool Callback(const std::string& pHook, int pArgCount = 0, const std::function<void()>& pArgFunc = nullptr, bool pDefaultReturn = true);
	}
}

#endif
