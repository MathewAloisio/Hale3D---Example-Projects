/*----------------------------------/
/--------------Skybox---------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
//#ifndef HALE3D_SKYBOX
//#define HALE3D_SKYBOX
//#pragma once
//
///*Standard Includes*/
//#include <string>
//
///*Hale3D Includes*/
//#include "../Core/Entity.h"
//
//namespace Hale3D {
//	class Shader;
//	class Texture;
//
//	class Skybox : public Entity {
//	public:
//		DECLARE_ENTITY_CLASS(Skybox);
//
//		Skybox();
//		~Skybox();
//
//		inline virtual bool IsSkybox() {
//			return true;
//		}
//
//		void SetCubemap(const std::string& pPath);
//		void SetCubemap(const std::string& pName, std::array<std::string, 6>& pFiles);
//		void SetShader(const std::string& pPath);
//		void SetPath(const std::string& pPath);
//		Shader* GetShader();
//		Texture* GetCubemap();
//		std::string GetPath();
//
//		virtual void PreDraw();
//		virtual void PostDraw();
//
//	private:
//		int oldCullFaceMode;
//		int oldDepthFuncMode;
//		Shader* shader = nullptr;
//		Texture* cubemap = nullptr;
//		std::string path;
//	};
//}
//#endif
