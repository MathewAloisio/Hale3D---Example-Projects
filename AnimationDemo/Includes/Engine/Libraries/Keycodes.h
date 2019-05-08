/*----------------------------------/
/-------------Keycodes--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_KEYCODES
#define HALE3D_KEYCODES

#include "../Libraries/Util.h"

/*Include GLFW*/
#include <GLFW/glfw3.h>

/* Standard include(s). */
#include <map>

namespace Hale3D {
	// Mouse inputs.
	enum class MouseButton : int32_t { //lua
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Right = GLFW_MOUSE_BUTTON_RIGHT
	};


	// Keyboard inputs.
	enum class Key : int32_t { //lua
		// ASCII Key.
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,

		// Misc. keys.
		Tab = GLFW_KEY_TAB,
		Equal = GLFW_KEY_EQUAL,
		Escape = GLFW_KEY_ESCAPE,
		Home = GLFW_KEY_HOME,
		Minus = GLFW_KEY_MINUS,
		Slash = GLFW_KEY_SLASH,
		Space = GLFW_KEY_SPACE,
		Comma = GLFW_KEY_COMMA,
		Insert = GLFW_KEY_INSERT,
		Enter = GLFW_KEY_ENTER,
		Delete = GLFW_KEY_DELETE,
		Pause = GLFW_KEY_PAUSE,
		Period = GLFW_KEY_PERIOD,
		NumLock = GLFW_KEY_NUM_LOCK,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		SemiColon = GLFW_KEY_SEMICOLON,
		Backspace = GLFW_KEY_BACKSPACE,
		BackSlash = GLFW_KEY_BACKSLASH,
		Apostrophe = GLFW_KEY_APOSTROPHE,
		GraveAccent = GLFW_KEY_GRAVE_ACCENT,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		RightBacket = GLFW_KEY_RIGHT_BRACKET,

		// Arrow keys.
		Up = GLFW_KEY_UP,
		Down = GLFW_KEY_DOWN,
		Left = GLFW_KEY_LEFT,
		Right = GLFW_KEY_RIGHT,

		// Numpad keys.
		Numpad0 = GLFW_KEY_KP_0,
		Numpad1 = GLFW_KEY_KP_1,
		Numpad2 = GLFW_KEY_KP_2,
		Numpad3 = GLFW_KEY_KP_3,
		Numpad4 = GLFW_KEY_KP_4,
		Numpad5 = GLFW_KEY_KP_5,
		Numpad6 = GLFW_KEY_KP_6,
		Numpad7 = GLFW_KEY_KP_7,
		Numpad8 = GLFW_KEY_KP_8,
		Numpad9 = GLFW_KEY_KP_9,

		NumpadAdd = GLFW_KEY_KP_ADD,
		NumpadEnter = GLFW_KEY_KP_ENTER,
		NumpadDivide = GLFW_KEY_KP_DIVIDE,
		NumpadDecimal = GLFW_KEY_KP_DECIMAL,
		NumpadSubtract = GLFW_KEY_KP_SUBTRACT,
		NumpadMultiply = GLFW_KEY_KP_MULTIPLY,

		// Function keys.
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,


		// Unknown key.
		Unknown = GLFW_KEY_UNKNOWN
	};

	// Key translation table.
	typedef std::map<std::string, Key> KeyTranslationMap;
	namespace Keycodes {
		std::string GetKeyName(Key pKey); //lua
		Key GetKeyByName(const std::string& pKeyName); //lua
	}
}

#endif
