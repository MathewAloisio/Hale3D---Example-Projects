/*----------------------------------/
/---------------Device--------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_DEVICE
#define HALE3D_DEVICE
#pragma once

/*Standard Includes*/
#include <string>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	class Context;
	struct DeviceBuffer;

	class Device { 
	public:
		Device(Context* pContext);
		~Device();

		VkDevice logical; // Vulkans logical representation of the physical device.
		VkCommandPool commandPool;
		VkPhysicalDevice physical; // Vulkans physical device representation.
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceProperties properties; // Physical device properties.
		VkPhysicalDeviceMemoryProperties memoryProperties;
		std::vector<std::string> supportedExtensions;
		struct {
			struct {
				uint32_t compute;
				uint32_t graphics;
				uint32_t transfer;
			} indices;
			std::vector<VkQueueFamilyProperties> properties;
		} queueFamily;

		bool IsExtensionSupported(const std::string& pExtension);
		uint32_t GetMemoryType(uint32_t pTypeBits, VkMemoryPropertyFlags pProperties, VkBool32* pMemTypeFound = nullptr);
		uint32_t GetQueueFamilyIndex(VkQueueFlagBits pQueueFlags);
		VkCommandPool CreateCommandPool(uint32_t pQueueFamilyIndex, VkCommandPoolCreateFlags pFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		void CreateBuffer(VkBuffer& pBuffer, const VkBufferUsageFlags& pUsage, const VkMemoryPropertyFlags& pMemProps, VkDeviceMemory& pMemory, VkDeviceSize pSize, void* pData = nullptr);
		void CreateBuffer(DeviceBuffer& pBuffer, const VkBufferUsageFlags& pUsage, const VkMemoryPropertyFlags& pMemProps, VkDeviceSize pSize, void* pData = nullptr);
		void PrintPhysicalDeviceInfo();

	private:
		Context* context;
		VkPhysicalDeviceFeatures enabledFeatures;

		void SelectPhysicalDevice(); // Selects best physical device based on generated rating.
		void CreateLogicalDevice(bool pUseSwapchain = true, VkQueueFlags pRequestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
	};
}
#endif
