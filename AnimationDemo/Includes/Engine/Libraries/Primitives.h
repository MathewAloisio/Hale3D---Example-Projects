/*----------------------------------/
/------------Primitives-------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PRIMITIVES
#define HALE3D_PRIMITIVES
#include "../Structs/Vertex.h"
#include "../Libraries/Math.h"

/* Standard include(s). */
#include <array>
#include <vector>

namespace Hale3D {
	class Primitive2D {
	public:
		Primitive2D() = default;
		Primitive2D(const Primitive2D& pOther) = default;
		Primitive2D(Primitive2D&& pMovable) = default;

		void Append(const Primitive2D& pAppendable);

		Primitive2D& operator=(const Primitive2D& pOther) = default;
		Primitive2D& operator=(Primitive2D&& pMovable) = default;

		const std::vector<Vector2>& GetVertexPositions() const;
		const std::vector<Vector2>& GetTextureCoordinates() const;
		std::vector<Vertex2D> GetVertices() const;

		// Static method(s)
		static Primitive2D GenerateArc(const Vector2& pCenter, float pRadius, float pStartAngle, float pArcAngle, int pSideCount = -1, bool pGenerateTexCoords = true);
		static Primitive2D GenerateCircle(float pRadius, int pSideCount = -1, bool pGenerateTexCoords = true);
		static Primitive2D GenerateBezier(const std::array<Vector2, 4>& pPoints, int pSideCount = -1, bool pGenerateTexCoords = true);
		static Primitive2D GenerateRoundedRectangle(const Vector2& pSize, const RectangleRadiuses& pRadiuses, bool pGenerateTexCoords = true);

	private:
		struct {
			std::vector<Vector2> positions;
			std::vector<Vector2> textureCoords;
		} _vertex;
	};
}


#endif
