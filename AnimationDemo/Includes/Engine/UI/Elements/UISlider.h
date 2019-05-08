/*----------------------------------/
/--------------UISlider-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_UI_ELEMENT_SLIDER
#define HALE3D_UI_ELEMENT_SLIDER

#include "../UIElement.h"
#include "../../Structs/Vector2.h"
#include "../../Structs/EnumerateArray.h"
#include "../../Rendering/RenderTarget.h"

namespace Hale3D {
	enum class UISliderElement : uint8_t { //lua
		HorizontalLine,	// The horizontal line the button moves along.
		VerticalLines,	// The vertical step marker lines.
		Button			// The button to move the slider with.
	};

	class UISlider : public UIElement { //lua
	public:
		// Constructor(s) & destructor(s).
		UISlider(const Vector2& pUpperLeft, float pWidth, float pHeight); //lua
		UISlider(const Vector2& pUpperLeft, const Vector2& pLowerRight); //lua

		// Mouse & keyboard control.
		virtual bool IsMouseInside() const;

		// Mouse & keyboard callbacks.
		virtual void OnMousePressed(MouseButton pButton);
		virtual void OnMouseReleased(MouseButton pButton);

		// General callbacks.
		virtual void OnUpdate();

		// Rendering & visibility.
		virtual void Draw();

		// Color & aesthetics.
		void SetColor(UISliderElement pElement, const Color4& pColor);
		const Color4& GetColor(UISliderElement pElement);

		// Value control.
		void SetMinimum(float pMinimum);
		void SetMaximum(float pMaximum);
		const float& GetMinimum() const;
		const float& GetMaximum() const;

		void SetStep(float pStep);
		const float& GetStep() const;

		void SetValue(float pValue);
		const float& GetValue() const;

	private:
		// RenderTarget management - private.
		void _RebuildRenderTarget();

		// Color & aesthetics.
		EnumerateArray<UISliderElement, Color4, 3> _colors;

		// Position & transformations.
		struct {
			Vector2 start;
			Vector2 end;
		} _transform;

		// Cache & state members.
		bool _sliding;
		bool _rebuildRenderTarget;
		RenderTarget _renderTarget;

		struct {
			float current;	// The current value of the slider.
			float step;		// How much to +/- the slider by per unit of mouse x-axis movement.
		} _value;

		struct {
			float min;
			float max;
		} _limits;
	};
}

#endif
