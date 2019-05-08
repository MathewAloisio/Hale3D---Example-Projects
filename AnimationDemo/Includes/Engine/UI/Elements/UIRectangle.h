/*----------------------------------/
/------------UIRectangle------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_UI_ELEMENT_RECTANGLE
#define HALE3D_UI_ELEMENT_RECTANGLE

/* Include directive(s). */
#include "../UIElement.h"
#include "../../Structs/Color4.h"
#include "../../Structs/EnumerateArray.h"
#include "../../Libraries/Math.h"
#include "../../Rendering/Texture.h"

namespace Hale3D {
	class UIRectangle : public UIElement { //lua
	public:
		UIRectangle(const Vector2& pUpperLeft, float pWidth, float pHeight, const Color4& pColor = Color4(0, 0, 0, 255)); //lua
		UIRectangle(const Vector2& pUpperLeft, const Vector2& pLowerRight, const Color4& pColor = Color4(0, 0, 0, 255)); //lua

		// Color & asthetics.
		void SetColor(const Color4& pColor); //lua
		Color4 GetColor() const; //lua

		void SetTexture(const std::string& pPath = ""); //lua
		Texture* GetTexture() const; //lua

		void SetFillMode(bool pFill); //lua
		bool GetFillMode() const; //lua

		void SetStartPoint(const Vector2& pUpperLeft); //lua
		Vector2 GetStartPoint() const; //lua

		void SetEndPoint(const Vector2& pLowerRight); //lua
		Vector2 GetEndPoint() const; //lua

		Vector2 GetCenter() const; //lua

		/*--WARNING: ONLY affects resizing behavior!--*/
		void SetMinimumWidth(float pWidth); //lua
		void SetMaximumWidth(float pWidth); //lua
		float GetMinimumWidth() const; //lua
		float GetMaximumWidth() const; //lua

		void SetMinimumHeight(float pHeight); //lua
		void SetMaximumHeight(float pHeight); //lua
		float GetMinimumHeight() const; //lua
		float GetMaximumHeight() const; //lua
		/*------------------------------------------*/

		float GetWidth() const; //lua
		float GetHeight() const; //lua

		// Configuration & settings.
		void SetResizable(bool pResizable); //lua
		bool IsResizable() const; //lua

		void SetCornerThreshold(float pThreshold); //lua
		float GetCornerThreshold() const; //lua

		void SetMoveable(bool pMoveable); //lua
		bool IsMoveable() const; //lua

		void SetMoveZoneBounds(const RectangleBounds& pBounds);
		const RectangleBounds& GetMoveZoneBounds() const;

		// NOTE: Move zone factors scale from 0.f to 1.f representing percentage of UIRect width away from the RectanglePoint.
		// RectangleBounds{ 0.f, 0.f, 0.f, 0.f } would be a fully moveable menu, where as RectangleBounds{ 0.f, 0.f, 0.75f, 0.f } would be a menu moveable only by the top 15 percent of the UI menu's height, but the entire width.
		void SetMoveZoneFactors(const RectangleBounds& pFactors);
		const RectangleBounds& GetMoveZoneFactors() const;

		// Mouse & keyboard control.
		virtual bool IsMouseInside() const; //lua

		// Mouse & keyboard callbacks.
		virtual void OnMousePressed(MouseButton pButton);
		virtual void OnMouseReleased(MouseButton pButton);

		// General callbacks.
		virtual void OnUpdate();

		// Rendering & visibility.
		virtual void Draw();

		// UIRect Instance.
		bool IsMoving() const; //lua
		bool IsResizing() const; //lua
		const RectanglePoints& GetCornerPoints() const; //lua

		const RectangleBounds& GetBounds() const; //lua

		// UIRect Callbacks.
		virtual void OnResized() {};

	protected:
		struct {
			bool fill;
			Color4 color;
			Texture* texture;
		} _appearance;

		struct {
			bool resizable;
			bool moveable;
			RectangleBounds moveZoneBounds;
			float cornerThreshold;
		} _settings;

		struct {
			struct {
				Vector2 start;
				Vector2 end;
			} lastSizeTranslation;

			struct {
				float width;
				float height;
			} min;

			struct {
				float width;
				float height;
			} max;

			RectanglePoint resizing;
			RectangleBounds moveZoneFactors;
			Vector2 movingOffset;
			bool validBounds;
			RectangleBounds bounds;
			RectanglePoints cornerPoints;
		} _uirect;

		void _RecalculateMoveZoneFactors();
		void _RebuildMoveZoneBounds();
		void _RebuildBounds();

		struct {
			Vector2 start;
			Vector2 end;
		} _translation;
	};
}

#endif
