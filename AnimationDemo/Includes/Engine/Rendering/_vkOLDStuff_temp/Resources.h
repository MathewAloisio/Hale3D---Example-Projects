/*----------------------------------/
/------------Resources--------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_RESOURCES
#define HALE3D_RESOURCES
#pragma once

/*Standard Includes*/
#include <unordered_map>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	class Context;
	class Texture;
	class Shader;

	/*Note: ResourceList's make no assumptions in regards to allocation/deallocation of the structure they contain.*/
	template <typename T>
	class ResourceList {
	public:
		ResourceList() {
			context = Context::GetCurrent();
		}

		inline const T Get(const std::string& pResource) {
			return resources[pResource];
		}

		inline bool Exists(const std::string& pResource) {
			return resources.find(pResource) != resources.end();
		}

		std::unordered_map<std::string, T> resources;

	protected:
		Context* context; //The graphics context that these resources belong to.
	};

	class TextureList : public ResourceList<Texture*> {
	public:
		~TextureList();

		Texture* AddTexture(const std::string& pName, const std::string& pFile, VkImageUsageFlags pImageUsage = VK_IMAGE_USAGE_SAMPLED_BIT);
		Texture* Add(const std::string& pName, Texture* pCubemap);
		void Remove(const std::string& pName);
	};

	class Resources {
	public:
		TextureList textures;
	};
}
#endif
