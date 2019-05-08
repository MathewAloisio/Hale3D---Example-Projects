/*----------------------------------/
/--------------Model----------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_MODEL
#define HALE3D_MODEL

#include "Animation.h"
#include "../Structs/AABB.h"

/* Standard include(s). */
#include <map>
#include <string>
#include <array>

namespace Hale3D {
	class ExpandingBuffer;
	/*Model | Supports a custom MDL format created for Hale3D.*/
	typedef std::array<uint32_t, 3> Triangle;

	struct Weight {
		float m_Bias;
		int32_t m_JointID;
		Vector3 m_Position;
	};

	struct VertexInfo { // Vertex information as stored in file.
		Vector2 m_UVCoords;

		struct {
			uint32_t m_Start;
			uint32_t m_Count;
		} m_Weight;
	};

	class Model;
	struct Mesh;
	class MeshBuffer { // Contains the computed vertices of a mesh, each ModelBuffer owns a MeshBuffer[model->m_Meshes.size()]. (TODO: Pool alike mesh buffers in the future and store pointers to them.)
	public:
		std::vector<Vertex> m_VertexArray;
		std::vector<uint32_t> m_VertexIndex;
		std::vector<Vector3> m_BindPoseNormals; // Bind-pose normals in joint-local space.

		void SetMesh(Model* pModel, size_t pMeshIndex);
		void PrepareBindPoseMesh(const Skeleton& pSkeleton);
		void ComputeVertexPositions(const Skeleton& pSkeleton);
		void ComputeVertexTextureCoords();
		void ComputeVertexNormals(const Skeleton& pSkeleton);
		void ComputeVertexTangents(const Skeleton& pSkeleton);
		void ComputeVertexBitangents(const Skeleton& pSkeleton);

	private:
		size_t _meshIndex;
		Model* _model;
	};

	class ModelBuffer {
	public:
		void SetModel(Model* pModel);
		void ComputeMesh(size_t pMeshIndex);
		void ComputeAllMeshes();
		void PrepareBindPoseModel();

		const MeshBuffer& GetMeshBuffer(size_t pMeshIndex) const;
		const std::vector<MeshBuffer>& GetMeshBuffers() const;

		Skeleton& GetSkeleton();
		const Skeleton& GetSkeleton() const;

	private:
		Skeleton _skeleton;
		std::vector<MeshBuffer> _meshBuffers;
	};

	struct Mesh {
		std::vector<VertexInfo> m_VertexInfo;
		std::vector<Weight> m_Weights;
		std::vector<Triangle> m_Triangles;
		std::string m_Material;
	};

	class Model : public Object {
	public:
		/* Methods. */
		bool Save(const std::string& pPath, bool pOverwrite = false) const;
		bool IsAnimationValid(Animation* pAnimation) const; // Checks if model supports pAnimation.
		std::string GetPath() const;
		const AABB& GetBindPoseAABB() const;
		ModelBuffer& GetBindPoseBuffer();
		const ModelBuffer& GetBindPoseBuffer() const;

		virtual void Remove();

		/* Data. */
		std::vector<Mesh> m_Meshes;

		/* Static methods. */
		static Model* Load(const std::string& pPath);
		
		/* Static constant members. */
		static constexpr uint32_t UniqueIdentifier = ('M' << 24) + ('D' << 16) + ('3' << 8) + 'H'; // Used to confirm that a file contains an engine-supported model.
		static constexpr uint32_t CurrentVersion = 1;

	private:
		AABB _bindposeAABB;
		std::string _path;
		ModelBuffer _modelBuffer; // Bind-pose model buffer.

		/* Reference counting. */
		static ReferenceTable<Model*> _modelReference;

		/* Static private methods. */
		static void __ReadData(Model& pModel, ExpandingBuffer& pBuffer);
	};
}

#endif
