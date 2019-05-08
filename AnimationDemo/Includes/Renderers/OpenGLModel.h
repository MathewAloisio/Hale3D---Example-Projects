/*----------------------------------/
/------------OpenGLModel------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLMODEL
#define HALE3D_EXTERNAL_OGLMODEL

/*Hale3D Include(s)*/
#include "Engine/Libraries/Model.h"

namespace Hale3D {
	struct OpenGLMesh {
		OpenGLMesh();
		~OpenGLMesh();

		uint32_t m_VertexArrayID;
		uint32_t m_VertexBufferID;
		uint32_t m_IndexBufferID;

		void Unbind();
		void Bind(const MeshBuffer& pMeshBuffer);
		void Draw(const MeshBuffer& pMeshBuffer);
	};

	struct OpenGLModel {
		OpenGLModel(Model* pModel);
		~OpenGLModel();

		std::vector<OpenGLMesh> m_Meshes;
	};
}

#endif
