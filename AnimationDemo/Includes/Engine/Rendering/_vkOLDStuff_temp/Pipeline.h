/*----------------------------------/
/-------------Pipeline--------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_PIPELINE
#define HALE3D_PIPELINE
#pragma once

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	/*Descriptor Sets & Descriptor Set Layouts.*/
	struct DescriptorSetLayout {
		DescriptorSetLayout(VkDevice pDevice, const VkDescriptorSetLayoutCreateInfo& pInfo);
		~DescriptorSetLayout();

		VkDevice device;
		VkDescriptorSetLayout layout;
	};

	class DescriptorSet {
	public:
		DescriptorSet(VkDevice pDevice, VkDescriptorPool pPool, const VkDescriptorSetAllocateInfo& pInfo);
		~DescriptorSet();

		void Clear();
		void Write(VkDescriptorType pType, uint32_t pLocation, VkDescriptorImageInfo* pImageInfo);
		void Write(VkDescriptorType pType, uint32_t pLocation, VkDescriptorBufferInfo* pBufferInfo);
		void Update(); // Updates the descriptorSet.

	private:
		VkDevice device;
		VkDescriptorSet descriptorSet;
		VkDescriptorPool descriptorPool;
		std::vector<VkWriteDescriptorSet> writeDescriptorSets;
	};

	enum PipelineType {
		Graphics,
		Compute
	};

	struct PipelineLayout {
		PipelineLayout(VkDevice pDevice, const VkPipelineLayoutCreateInfo& pInfo);
		~PipelineLayout();

		VkDevice device;
		VkPipelineLayout layout;
		DescriptorSet* descriptorSet;
		DescriptorSetLayout* descriptorSetLayout;
	};

	class Pipeline {
	public:
		/*Graphics Pipeline constructor.*/
		Pipeline(VkDevice& pDevice, const VkGraphicsPipelineCreateInfo& pInfo, VkPipelineCache pCache = VK_NULL_HANDLE);		
		/*Compute Pipeline constructor.*/
		Pipeline(VkDevice& pDevice, const VkComputePipelineCreateInfo& pInfo, VkPipelineCache pCache = VK_NULL_HANDLE);
		~Pipeline();
		
		PipelineType GetType();
		VkPipeline& GetPipeline();

	private:
		PipelineType type;
		VkDevice device;
		VkPipeline pipeline = VK_NULL_HANDLE;
	};
}
#endif
