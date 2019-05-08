#ifndef HALE3D_KEYBINDS
#define HALE3D_KEYBINDS

#include "Keycodes.h"

/* Standard include(s). */
#include <map>
#include <string>
#include <functional>

namespace Hale3D {
	namespace Keybinds {
		typedef std::map<Key, std::string> KeybindMap;
		struct _StaticBind {
			_StaticBind(Key pKey, std::string pCommand);
		};

		// Save & load.
		void Save(const std::string& pPath); //lua
		bool Load(const std::string& pPath); //lua

		// General.
		void CheckInputs();
		void Bind(const std::string& pBind, const std::string& pKey);
		std::string Get(Key pKey); //lua
		std::string Get(const std::string& pKey); //lua

		// Callback(s).
		void SetBindCallback(const std::function<void()>& pCallback);
	}
}

/* Helper macros. */
#define BIND_KEY(pKey, pCommand) static Keybinds::_StaticBind CREATE_VAR_NAME(keybind, __LINE__)(pKey, pCommand);

#endif
