/*----------------------------------/
/-----------PointLight--------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_POINTLIGHT
#define HALE3D_POINTLIGHT

/*Hale3D Includes*/
#include "../Core/Entity.h"

namespace Hale3D {
	class PointLight : public Entity { //lua
	public:
		DECLARE_ENTITY_CLASS(PointLight) //lua

		/* Constructor(s) & destructor(s). */
		PointLight();
		virtual ~PointLight();

		void SetRadius(float pRadius);
		float GetRadius() const;

		void SetColor(const Vector3& pColor);
		const Vector3& GetColor() const;

	private:
		float _radius;
		Vector3 _color;
	};
}

#endif
