/*----------------------------------/
/------------VulkanDevice-----------/
/-------Hale Game Engine 2018-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_EXTERNAL_VULKANDEVICE
#define HALE3D_EXTERNAL_VULKANDEVICE
#pragma once

/*Standard Includes*/
#include <string>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	class VulkanDeviceBuffer {
	public:
		VulkanDeviceBuffer() : _map(nullptr) {}

		void Map(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void Unmap();
		bool IsMapped() const;

		void Copy(void* pData, VkDeviceSize pDataSize);
		void Bind(VkDeviceSize pOffset = 0);
		void Flush(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void Invalidate(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void SetupDescriptor(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);

		VkDeviceMemory& GetMemory();
		VkDeviceMemory& GetMemorySize();
		VkDeviceMemory& GetMemoryAlignment();

		VkBuffer& GetBuffer();
		VkBufferUsageFlags& GetBufferUsage();
		VkDescriptorBufferInfo& GetBufferDescriptor();

		void* GetMap();
		VkMemoryPropertyFlags& GetMemoryProperties();

	private:
		VkDevice _device;
		VkDeviceMemory _deviceMemory;
		VkDeviceSize _deviceMemorySize;
		VkDeviceSize _deviceMemoryAlignment;

		VkBuffer _buffer;
		VkBufferUsageFlags _bufferUsage;
		VkDescriptorBufferInfo _bufferDescriptor;

		void* _map;
		VkMemoryPropertyFlags _memoryProperties;
	};

	class VulkanDevice { 
	public:
		VulkanDevice();
		~VulkanDevice();

		bool IsExtensionSupported(const std::string& pExtension);
		uint32_t GetMemoryType(uint32_t pTypeBits, VkMemoryPropertyFlags pProperties, VkBool32* pMemTypeFound = nullptr);
		uint32_t GetQueueFamilyIndex(VkQueueFlagBits pQueueFlags);
		VkCommandPool CreateCommandPool(uint32_t pQueueFamilyIndex, VkCommandPoolCreateFlags pFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		void CreateBuffer(VkBuffer& pBuffer, const VkBufferUsageFlags& pUsage, const VkMemoryPropertyFlags& pMemProps, VkDeviceMemory& pMemory, VkDeviceSize pSize, void* pData = nullptr);
		void CreateBuffer(VulkanDeviceBuffer& pBuffer, const VkBufferUsageFlags& pUsage, const VkMemoryPropertyFlags& pMemProps, VkDeviceSize pSize, void* pData = nullptr);
		void PrintPhysicalDeviceInfo();

	private:
		struct {
			VkDevice logical;
			VkPhysicalDevice physical;
		} _devices;

		struct {
			VkPhysicalDeviceFeatures physicalDeviceFeatures;
			VkPhysicalDeviceProperties physicalDeviceProperties;
			VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;

			std::vector<std::string> supportedExtensions;
		} _info;

		VkCommandPool _commandPool;
		VkPhysicalDeviceFeatures _enabledFeatures;

		struct {
			struct {
				uint32_t compute;
				uint32_t graphics;
				uint32_t transfer;
			} indices;
			std::vector<VkQueueFamilyProperties> properties;
		} _queueFamily;

		void _SelectPhysicalDevice(); // Selects best physical device based on generated rating.
		void _CreateLogicalDevice(bool pUseSwapchain = true, VkQueueFlags pRequestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);
	};
}
#endif
