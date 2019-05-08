/*----------------------------------/
/-----------OpenGLShader------------/
/-------Hale Game Engine 2019-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_OGLSHADER
#define HALE3D_EXTERNAL_OGLSHADER

/* OpenGLRenderer include(s). */
#include "OpenGLTools.h"

/*Hale3D Include(s)*/
#include "Engine/Structs/Vertex.h"
#include "Engine/Structs/Matrix4.h"
#include "Engine/Structs/EnumerateArray.h"

/*Standard Include(s)*/
#include <map>

namespace Hale3D {
	enum class OpenGLShaderType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Evaluation = GL_TESS_EVALUATION_SHADER,
		Control = GL_TESS_CONTROL_SHADER
	};

	class OpenGLShader {
	public:
		OpenGLShader();
		~OpenGLShader();

		void Link(const std::string& pShaderName = "UNNAMED");
		void Bind();
		void Unbind();
		bool IsCurrent();
		bool IsLinked();
		unsigned int GetID();
		float GetFloat(const std::string& pName);
		int GetInt(const std::string& pName);
		Vector2 GetVector2(const std::string& pName);
		Vector3 GetVector3(const std::string& pName);
		Vector4 GetVector4(const std::string& pName);
		Matrix4 GetMatrix4(const std::string& pName);
		void SetFloat(const std::string& pName, float pValue);
		void SetInt(const std::string& pName, int pValue);
		void SetVector2(const std::string& pName, const Vector2& pVector);
		void SetVector3(const std::string& pName, const Vector3& pVector);
		void SetVector4(const std::string& pName, const Vector4& pVector);
		void SetMatrix4(const std::string& pName, const Matrix4& pMatrix);
		void SetTexture(const std::string& pName, int pIndex);
		void SetFragDataLocation(int pID, const std::string& pName);
		void AddSource(const std::string& pSource, int pShaderType);
		void BindAttribLocation(int pLocation, const std::string& pName);
		const std::string& GetShaderError() const;
		const std::string& GetProgramError() const;

		/* Static constant(s). */
		static const std::vector<std::pair<std::string, OpenGLShaderType>> ORDERED_SHADER_EXTENSIOINS; // An array of accepted shader extensions, in correct linking order.

		/* Static nethods. */
		static OpenGLShader* Load(const std::string& pShaderPath, int pOutColorLoc = 0, const std::string& pOutColorName = "outColor");
		static OpenGLShader* CreateShader();

	private:
		int CheckUniformLocation(const std::string& pName);

		bool linked;
		unsigned int program; // Program
		unsigned int instance; // Shader (Only used for source-created shaders.)
		std::string name;
		std::string shaderError;
		std::string programError;
		std::map<OpenGLShaderType, unsigned int> instances; // Shaders
	};
}

/* Shader refresh. *//*
typedef std::map<Hale3D::OpenGLShaderType, time_t> _GLSLShaderModTimes;
typedef std::map<std::string, _GLSLShaderModTimes> _GLSLShaderMap;

void _RegisterGLSLShaderFile(const std::string& pPath, Hale3D::Shader* pEngineShader, const _GLSLShaderModTimes& pShaderModificationTimes);
void _DeregisterGLSLShaderFile(const std::string& pPath);
const _GLSLShaderMap& GetGLSLShaderMap();*/

#endif
