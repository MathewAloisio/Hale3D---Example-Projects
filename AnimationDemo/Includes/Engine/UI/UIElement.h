/*----------------------------------/
/------------UIElement--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_UIELEMENT
#define HALE3D_UIELEMENT

#include "../Structs/Vector2.h"
#include "../Libraries/Keycodes.h"
#include "../Rendering/Renderer.h"

/* Standard include(s). */
#include <string>
#include <vector>
#include <functional>

namespace Hale3D {
	class Window;

	class UIElement { //lua
	public:
		UIElement(); //lua
		UIElement(Window* pWindow); //lua
		virtual ~UIElement(); //lua

		// Lua communication.
		void RunLuaFunction(const std::string& pFuncName, int pArgCount = 0, const std::function<void()>& pArgsFn = nullptr);
		bool CallLuaFunction(const std::string& pFuncName, bool pDefaultReturn = true, int pArgCount = 0, const std::function<void()>& pArgsFn = nullptr);

		// Rendering & visibility.
		void SetHidden(bool pHidden); //lua
		bool IsHidden(); //lua
		virtual void Draw() {}; //lua

		Window* GetWindow(); //lua

		// Parenting & ownership.
		void SetParent(UIElement* pParentElement); //lua
		UIElement* GetParent(); //lua

		const std::vector<UIElement*>& GetChildren();
			
		// Mouse & keyboard control.
		void SetMouseHoverDelay(double pHoverDelay); //lua
		double GetMouseHoverDelay() const; //lua
		virtual bool IsMouseInside() const { return false; }; //lua
		virtual bool IsMouseHovering() const; //lua
			
		// Mouse & keyboard callbacks.
		virtual void OnMouseEnter() {};
		virtual void OnMouseExit() {};
		virtual void OnMousePressed(MouseButton pButton) {};
		virtual void OnMouseReleased(MouseButton pButton) {};
		virtual void OnMouseStartHovering() {};
		virtual void OnMouseStopHovering() {};
		virtual void OnMouseHovering() {};

		virtual void OnKeyPressed(Key pKey) {};
		virtual void OnKeyReleased(Key pKey) {};
			
		// General.
		void Update();
		void DetachFromWindow(bool pRemoveWindowChildren = true); //lua
		void SetEnabled(bool pEnabled); //lua
		bool GetEnabled() const; //lua

		// General callbacks.
		virtual void OnUpdate() {};
		virtual void OnFileDrop(const std::vector<std::string>& pFiles) {};

		virtual void OnPreDraw() {};
		virtual void OnPostDraw() {};

		/* Class control. */
		void SetClass(const std::string& pClass); //lua
		const std::string& GetClass() const; //lua

	protected:
		// (Protected) General.
		bool _enabled;
		std::string _className;

		// (Protected) Parenting & ownership.
		UIElement* _parent;
		std::vector<UIElement*> _children;

		// (Protected) Rendering & visibility.
		bool _isHidden;
		
		// (Protected) Mouse & keyboard control.
		struct {
			bool isHovering; // Is the mouse hovering over the UIElement.
			bool wasInElement; // Was the mouse in the UIElement last frame?
			double hoverDelay; // Hover delay in ms before "IsMouseHovering()" returns true.
			double enteredTime; // The time that the mouse entered the UIElement last.
		} _mouse;

		Window* _parentWindow;

	private:
		void _Initialize();

	};
}

#endif
