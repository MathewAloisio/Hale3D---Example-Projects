/*----------------------------------/
/--------------Vertex---------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_VERTEX
#define HALE3D_VERTEX

#include "Vector2.h"
#include "Vector3.h"

namespace Hale3D {
	struct Vertex2D { //lua
		/* Constructor(s) & destructor(s). */
		Vertex2D(); //lua
		Vertex2D(const Vector2& pPosition, const Vector2& pTexture); //lua
		Vertex2D(const Vertex2D& pCopyable) = default; //lua
		Vertex2D(Vertex2D&& pMovable) = default;

		/* Member(s). */
		Vector3 m_Position; //lua
		Vector2 m_Texture; //lua

	    /* Operator overload(s). */
		Vertex2D& operator=(const Vertex2D& pCopyable) = default;
		Vertex2D& operator=(Vertex2D&& pMovable) = default;

		bool operator==(const Vertex2D& pOther) const; //lua
		bool operator!=(const Vertex2D& pOther) const;

		std::string ToString() const; //lua
	};

	struct Vertex { //lua
		/* Constructor(s) & destructor(s). */
		Vertex(); //lua
		Vertex(const Vector3& pPosition, const Vector2& pTexture, const Vector3& pNormal, const Vector3& pTangent, const Vector3& pBitangent); //lua
		Vertex(const Vertex& pCopyable) = default; //lua
		Vertex(Vertex&& pMovable) = default;

		/* Member(s). */
		Vector3 m_Position; //lua
		Vector2 m_Texture; //lua
		Vector3 m_Normal; //lua
		Vector3 m_Tangent; //lua
		Vector3 m_Bitangent; //lua

		/* Operator overload(s). */
		Vertex& operator=(const Vertex& pCopyable) = default;
		Vertex& operator=(Vertex&& pMovable) = default;

		bool operator==(const Vertex& pOther) const; //lua
		bool operator!=(const Vertex& pOther) const;
		
		/*General*/
		std::string ToString() const; //lua
	};
}

namespace std {
	template <> struct hash<Hale3D::Vertex> {
		size_t operator()(const Hale3D::Vertex& obj) const {
			return size_t((hash<Hale3D::Vector3>()(obj.m_Position) ^ hash<Hale3D::Vector2>()(obj.m_Texture) ^ hash<Hale3D::Vector3>()(obj.m_Normal) << 1) >> 1);
		}
	};
}

#endif
