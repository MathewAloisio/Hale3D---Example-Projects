/*----------------------------------/
/-------------Swapchain-------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_SWAPCHAIN
#define HALE3D_SWAPCHAIN
#pragma once

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	class Window;
	class Context;

	struct SwapchainBuffer {
		VkImage image;
		VkImageView imageView;
	};

	class Swapchain {
	public:
		Swapchain(Context* pContext);
		~Swapchain();

		/*Initialization*/
		void Initialize(uint32_t& pWidth, uint32_t& pHeight, bool pVSync = false);
		void Deinitialize();

		/*Image Aquisition*/
		void AcquireNextImage(VkSemaphore pSemaphore, uint32_t& pImageIndex);
	
		/*Queue Presentation*/
		void QueuePresent(VkQueue pQueue, uint32_t pImageIndex, VkSemaphore pSemaphore = VK_NULL_HANDLE);
	
		struct {
			uint32_t present = UINT32_MAX;
			uint32_t graphics = UINT32_MAX;
		} queueNodeIndex;
	private:
		Context* context;
		VkFormat colorFormat;
		VkColorSpaceKHR colorSpace;
		VkSurfaceKHR surface;
		VkSwapchainKHR swapchain = VK_NULL_HANDLE;

		std::vector<VkImage> images;
		std::vector<SwapchainBuffer> buffers;

		/*Function Pointers*/
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR fpGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR fpGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR fpGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkCreateSwapchainKHR fpCreateSwapchainKHR;
		PFN_vkDestroySwapchainKHR fpDestroySwapchainKHR;
		PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;
		PFN_vkAcquireNextImageKHR fpAcquireNextImageKHR;
		PFN_vkQueuePresentKHR fpQueuePresentKHR;
	};
}
#endif
