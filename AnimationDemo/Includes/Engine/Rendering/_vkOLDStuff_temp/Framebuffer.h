/*----------------------------------/
/------------Framebuffer------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_FRAMEBUFFER
#define HALE3D_FRAMEBUFFER
#pragma once

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

/*Include GLFW*/
#include <GLFW/glfw3.h>

/*Standard Include(s)*/
#include <vector>

namespace Hale3D {
	class Context;
	class Device;

	struct FBOAttachment {
		VkImage image;
		VkImageView imageView;
		VkDeviceMemory memory;
		VkFormat format;

		void Destroy(const VkDevice& pDevice) {
			vkDestroyImage(pDevice, image, nullptr);
			vkDestroyImageView(pDevice, imageView, nullptr);
			vkFreeMemory(pDevice, memory, nullptr);
		}

		bool HasDepth() {
			const std::array<VkFormat, 6> formats = {
				VK_FORMAT_D16_UNORM, VK_FORMAT_X8_D24_UNORM_PACK32,
				VK_FORMAT_D32_SFLOAT, VK_FORMAT_D16_UNORM_S8_UINT,
				VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D32_SFLOAT_S8_UINT
			};
			return std::find(formats.begin(), formats.end(), format) != std::end(formats);
		}

		bool HasStencil() {
			const std::array<VkFormat, 4> formats = {
				VK_FORMAT_S8_UINT, VK_FORMAT_D16_UNORM_S8_UINT,
				VK_FORMAT_D24_UNORM_S8_UINT, VK_FORMAT_D32_SFLOAT_S8_UINT
			};
			return std::find(formats.begin(), formats.end(), format) != std::end(formats);
		}

		bool IsDepthStencil() {
			return HasDepth() || HasStencil();
		}
	};

	class Framebuffer {
	public:
		struct AttachmentCreateInfo {
			AttachmentCreateInfo(VkFormat pFormat, uint32_t pWidth, uint32_t pHeight, VkImageUsageFlagBits pUsage, VkCommandBuffer pCommandBuffer);

			VkFormat format;
			uint32_t width;
			uint32_t height;
			VkImageUsageFlagBits usage;
			VkCommandBuffer commandBuffer;
		};

		Framebuffer(Device* pDevice, VkCommandPool& pPool, std::vector<AttachmentCreateInfo> pAttachments);
		~Framebuffer();

		void Bind();
		void Submit(const std::vector<VkCommandBuffer>& pSubBuffers);
		void Reset();
		void Unbind();
		void BlitTo(int pWidth, int pHeight, unsigned int pOtherFBO, int pOtherWidth, int pOtherHeight);
		
		FBOAttachment CreateAttachment(const AttachmentCreateInfo& pInfo);

		FBOAttachment& GetAttachment(size_t pIndex);
		VkFramebuffer& GetFBO();
		VkRenderPass& GetRenderPass();
		VkCommandBuffer& GetCommandBuffer();

	private:
		/*RenderPass*/
		void SetupRenderPass();
		void DestroyRenderPass();

		VkFramebuffer fbo;
		VkRenderPass renderPass;
		VkSubmitInfo submitInfo;
		VkCommandPool commandPool;
		VkCommandBuffer commandBuffer;
		Device* device;
		Context* context;
		std::vector<FBOAttachment> attachments;
	};
}
#endif
