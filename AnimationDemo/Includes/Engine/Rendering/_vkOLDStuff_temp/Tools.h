/*----------------------------------/
/--------------Tools----------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_TOOLS
#define HALE3D_TOOLS
#pragma once

/*Standard Includes*/
#include <assert.h>
#include <string>
#include <array>
#include <vector>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

/*Hale3D Include(s)*/
#include "Texture.h"
#include "../Libraries/System.h"

/*Hale3D Definitions*/
#define GL_CHECK_RESULT(GLResult)																															\
	if (!GLResult) {																																		\
		System::Print("[Rendering] Fatal: OpenGL reported failure. (File: \"" + std::string(__FILE__) + "\" | Line: " + std::to_string(__LINE__) + ".");	\
		assert(false);																																		\
	}

#define GL_GET_STRING(GLIn)																																	\
	std::string((char*)glGetString(GLIn))

namespace Hale3D {
	class Entity;

	namespace Tools {

		const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };

		void SwapRGBBGR(std::vector<unsigned char>& pValue);
		void SortRenderableEntities(std::vector<Entity*>& pEntities);
		bool IsValidTextureFormat(VkFormat pFormat);
		bool IsValidationSupported();
		unsigned int GetPhysicalDeviceRating(const VkPhysicalDevice& pDevice);
		std::string VkVersionToString(uint32_t pVersion);
		std::string VkResultToString(VkResult pResult);
		std::vector<const char*> RequiredVkInstanceExtensions();

		/*Vulkan Data Initialization tools.*/
		VkFormat GetSupportedDepthFormat(VkPhysicalDevice pDevice);
		VkViewport VkCreateViewport(uint32_t pWidth, uint32_t pHeight, float zNear, float zFar);
		VkRect2D VkCreateScissor(VkExtent2D pExtent, VkOffset2D pOffset);
		VkImageCreateInfo VkImageCreationInfo();
		VkDescriptorImageInfo VkDescriptorImageInfoEx(VkSampler pSampler, VkImageView pImageView, VkImageLayout pLayout = VK_IMAGE_LAYOUT_GENERAL);
		VkDescriptorSetAllocateInfo VkDescriptorSetAllocationInfo(VkDescriptorPool pPool, const VkDescriptorSetLayout* pSetLayouts, uint32_t pCount);
		VkDescriptorSetLayoutBinding VkDescriptorSetLayoutBindingEx(VkDescriptorType pType, VkShaderStageFlags pFlags, uint32_t pBinding, uint32_t pCount = 1);
		VkDescriptorSetLayoutCreateInfo VkDescriptorSetLayoutCreateInfoEx(const std::vector<VkDescriptorSetLayoutBinding>& pBindings);
		VkMemoryAllocateInfo VkMemoryAllocationInfo(VkDeviceSize pAllocationSize, uint32_t pMemType);
		VkDescriptorPoolSize VkDescriptionPoolSize(VkDescriptorType pType, uint32_t pCount);
		VkCommandBufferAllocateInfo VkCommandBufferAllocationInfo(const VkCommandPool& pPool, VkCommandBufferLevel pLevel, uint32_t pCount);
		VkPipelineVertexInputStateCreateInfo VkVertexInputStateCreateInfo(const VkVertexInputBindingDescription& pVertexBinding, const std::array<VkVertexInputAttributeDescription, 3>& pVertexAttribs);
		VkPipelineMultisampleStateCreateInfo VkMSAAStateCreateInfo(VkSampleCountFlagBits pSamples, const VkPipelineMultisampleStateCreateFlags& pFlags);
		VkPipelineDynamicStateCreateInfo VkDynamicStateCreateInfo(const std::vector<VkDynamicState>& pStates);
		VkPipelineViewportStateCreateInfo VkViewportStateCreateInfo(uint32_t pViewportCount, uint32_t pScissorCount, const VkPipelineViewportStateCreateFlags& pFlags = 0);
		VkPipelineShaderStageCreateInfo VkShaderStageCreateInfo(VkShaderModule pModule, VkShaderStageFlagBits pStages);
		struct DepthBounds {
			float min = 0.0f;
			float max = 0.0f;
		};
		VkPipelineDepthStencilStateCreateInfo VkDepthStencilStateCreateInfo(VkCompareOp pCompareOp, VkCompareOp pFrontCompareOp, VkCompareOp pBackCompareOp, VkBool32 pDepthTest = VK_TRUE, VkBool32 pDepthWrite = VK_TRUE, const DepthBounds& pDepthBounds = DepthBounds());
		VkPipelineInputAssemblyStateCreateInfo VkInputAssemblyStateCreateInfo(VkBool32 pPrimitiveRestart = VK_FALSE, VkPrimitiveTopology pTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
		VkPipelineRasterizationStateCreateInfo VkRasterizationStateCreateInfo(VkPolygonMode pPolygonMode, VkCullModeFlagBits pCullMode, VkFrontFace pFrontFace, VkBool32 pDepthClamp = VK_FALSE, float pLineWidth = 1.0f);
		VkPipelineColorBlendAttachmentState VkColorBlendAttachmentState(VkBool32 pEnable, VkBlendFactor pSrcColorBlendFactor = VK_BLEND_FACTOR_ONE, VkBlendFactor pDstColorBlendFactor = VK_BLEND_FACTOR_ONE, VkBlendOp pColorBlendOp = VK_BLEND_OP_ADD, VkBlendFactor pSrcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, VkBlendFactor pDstAlphaBlendFactor = VK_BLEND_FACTOR_ONE, VkBlendOp pAlphaBlendOp = VK_BLEND_OP_ADD);
		VkPipelineColorBlendStateCreateInfo VkColorBlendStateCreateInfo(uint32_t pAttachmentCount, const VkPipelineColorBlendAttachmentState& pAttachments);
		VkPipelineTessellationStateCreateInfo VkTesselationStateCreateInfo(uint32_t pPatchCtrlPoints);
		VkAttachmentDescription VkCreateAttachmentDescription(VkFormat pFormat, VkImageLayout pLayout);

		/*Function Procedure Address Lookup.*/
		template <typename T> T VkGetInstanceProcAddress(const VkInstance& pInstance, const char* pName) {
			return reinterpret_cast<T>(vkGetInstanceProcAddr(pInstance, pName));
		}

		template <typename T> T VkGetDeviceProcAddress(const VkDevice& pDevice, const char* pName) {
			return reinterpret_cast<T>(vkGetDeviceProcAddr(pDevice, pName));
		}
	}
}
#endif
