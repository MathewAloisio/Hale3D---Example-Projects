/*----------------------------------/
/-------------Window----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_WINDOW
#define HALE3D_WINDOW

/*Hale3D Includes*/
#include "../Core/Entity.h"
#include "../Structs/Matrix4.h"
#include "../Libraries/Keycodes.h"

/* Standard include(s). */
#include <vector>

/*Windows Forward Declaration(s).*/
#ifdef _WIN32
struct HWND__;
typedef HWND__* HWND;
#endif

namespace Hale3D {
	struct Vector2;
	class Context;

	enum class CursorMode : int32_t { //lua
		Active = GLFW_CURSOR_NORMAL,
		Hidden = GLFW_CURSOR_HIDDEN,
		Disabled = GLFW_CURSOR_DISABLED
	};

	class UIElement;
	class Window : public Object { //lua
	public:
		/* Constructor(s) & destructor(s). */
		Window(int pWidth, int pHeight, const std::string& pTitle, GLFWmonitor* pMonitor = nullptr); //lua
#ifdef _WIN32
		Window(HWND pHandle);
#endif
		virtual ~Window(); //lua

		/* Method(s). */
		// Return value: bool - window closed? true => window closed | false => window opened.
		virtual bool Update(); //lua

		void Fullscreen(GLFWmonitor* pMonitor = nullptr); //lua
		void Maximize(); //lua
		void Minimize(); //lua
		void Restore(); //lua
		void Close(); //lua
		void Show(); //lua
		void Hide(); //lua
		void Focus(); //lua
		void SetTitle(const std::string& pTitle); //lua
		void SetSize(const Vector2& pSize); //lua
		void SetPosition(const Vector2& pPosition); //lua
		void SetCursorPosition(const Vector2& pCursorPos) const; //lua
		
		/*Callbacks*/
		virtual void OnResized(int pWidth, int pHeight) {};
		virtual void OnFileDropped(const std::vector<std::string>& pFilePaths) {};
		virtual void OnKeyPressed(Key pKey) {};
		virtual void OnKeyReleased(Key pKey) {};
		virtual void OnMousePressed(MouseButton pButton) {};
		virtual void OnMouseReleased(MouseButton pButton) {};

		/*General*/
		Vector2 GetSize() const; //lua
		Vector2 GetPosition() const; //lua
		Vector2 GetCursorDelta() const; //lua
		Vector2 GetCursorPosition() const; //lua
		GLFWwindow* GetWindow();

		bool IsOwned() const; //lua Does the engine own the window?
		bool IsMaximized() const; //lua
		bool IsMinimized() const; //lua
		bool IsFocused() const; //lua
		bool IsFullscreen() const; //lua
		bool IsHidden() const; //lua
		bool ShouldClose() const; //lua

		/*Mouse & keyboard input.*/
		bool IsKeyDown(Key pKey) const; //lua
		bool IsMouseDown(MouseButton pMouseButton) const; //lua

		void SetCursorMode(CursorMode pMode); //lua
		CursorMode GetCursorMode() const; //lua

		void SetClipboard(const std::string& pData); //lua
		std::string GetClipboard() const; //lua

		/* Static methods. */
		static void SetCurrent(Window* pWindow); //lua
		static Window* GetCurrent(); //lua

		/* Static callbacks. */
		static void OnWindowResized(Window* pWindow, int pWidth, int pHeight);
		static void OnWindowFileDrop(Window* pWindow, const std::vector<std::string>& pFilePaths);
		static void OnWindowKeyPressed(Window* pWindow, Key pKey, int pScancode);
		static void OnWindowKeyReleased(Window* pWindow, Key pKey, int pScancode);
		static void OnWindowMousePressed(Window* pWindow, MouseButton pButton);
		static void OnWindowMouseReleased(Window* pWindow, MouseButton pButton);
		static void OnError(int pCode, const char* pError);

		/* Internal methods. */
		void _UIRegisterElement(UIElement* pElement);
		void _UIDeregisterElement(UIElement* pElement);

	protected:
		/* Members. */
		bool _focus;
		bool _hidden;
		bool _ownsWindow;
		GLFWwindow* _window;
		GLFWmonitor* _monitor;

		std::vector<UIElement*> _uiElements;

		struct {
			Vector2 last;
			Vector2 delta;
		} _cursorPos;

		/* Method(s). */
		void _SetupDefaultProperties();
	};
}

#endif
