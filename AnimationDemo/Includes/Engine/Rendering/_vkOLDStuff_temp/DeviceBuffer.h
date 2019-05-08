/*----------------------------------/
/------------DeviceBuffer-----------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_DEVICEBUFFER
#define HALE3D_DEVICEBUFFER
#pragma once

/*Standard Include(s)*/
#include <vector>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	/*Structure as all members are public.*/
	struct DeviceBuffer {
		void Destroy();

		void Map(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void Unmap();
		bool IsMapped();

		void Bind(VkDeviceSize pOffset = 0);
		void Invalidate(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void Flush(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);

		void SetupDescriptor(VkDeviceSize pSize = VK_WHOLE_SIZE, VkDeviceSize pOffset = 0);
		void Copy(void* pData, VkDeviceSize pSize);

		VkBuffer buffer;
		VkDevice device;
		VkDeviceMemory memory;
		VkDescriptorBufferInfo descriptor;
		VkDeviceSize size = 0;
		VkDeviceSize alignment = 0;
		VkBufferUsageFlags usage;
		VkMemoryPropertyFlags memoryProperties;
		void* mapped = nullptr;
	};
}
#endif
