/*----------------------------------/
/--------------AABB-----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_AABB
#define HALE3D_AABB

#include "Vector3.h"

namespace Hale3D {
	class AABB {
	public:
		/* Constructor(s) & destructor(s). */
		AABB();
		AABB(Vector3 pMin, Vector3 pMax);
		~AABB();

		/* Method(s). */
		bool IsBoxInside(const AABB& box);
		bool IsBoxIntersecting(const AABB& box);
		bool IsPointInside(const Vector3& position);
		bool IsSphereInside(const Vector3& position, const float radius);

		void SetMin(const Vector3& pMinimum);
		void SetMax(const Vector3& pMaximum);

		const Vector3& GetMin() const;
		const Vector3& GetMax() const;

		void ExtendMin(const Vector3& pPosition);
		void ExtendMax(const Vector3& pPosition);
		float GetWidth() const;
		float GetHeight() const;
		float GetDepth() const;

		Vector3 GetVertexPositive(const Vector3& pNormal) const;
		Vector3 GetVertexNegative(const Vector3& pNormal) const;

		float GetDiagonal() const;
		const Vector3& GetCenter() const;

	private:
		float _diagonalLength;
		Vector3 _min;
		Vector3 _max;
		Vector3 _center;

		void _RecalculateInfo();
	};
}

#endif
