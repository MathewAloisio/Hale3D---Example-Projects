/*----------------------------------/
/------------FlyCamera-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_FREECAMERA
#define HALE3D_FREECAMERA

/*Hale3D Includes*/
#include "Camera.h"
#include "../Rendering/Window.h"

namespace Hale3D {
	class Window;
	class FlyCamera : public Camera { //lua
	public:
		DECLARE_ENTITY_CLASS(FlyCamera) //lua

		FlyCamera();

		/*General.*/
		virtual void Update();

		virtual void OnMadeCurrent();
		virtual void OnMadeNonCurrent();

		// For performance reasons, the FlyCamera will handle the frustum rebuilding itself.
		virtual void SetPosition(const Vector3& pPosition);
		virtual void SetAngles(const Vector3& pAngles);
		virtual void SetRotation(const Quaternion& pRotation);

		void SetMoveSpeed(float pUnitsPerSecond); //lua
		float GetMoveSpeed() const; //lua

		void SetMouseSensitivity(float pSensitivity); //lua
		float GetMouseSensitivity() const; //lua

		void SetSpeedMultiplicationFactor(float pFactor); //lua
		float GetSpeedMultiplicationFactor() const; //lua

		void SetSpeedDivisionFactor(float pFactor); //lua
		float GetSpeedDivisionFactor() const; //lua

	private:
		float _moveSpeed;
		float _mouseSensitivity;
		CursorMode _pastCursorMode; // The cursor mode before this camera became active.

		struct {
			float FOV;
		} _defaults;

		Vector2 lastCursorPos;

		struct {
			float moveSpeedMultiplier;
			float moveSpeedDivisor;
		} _modifiers;
	};
}

#endif
