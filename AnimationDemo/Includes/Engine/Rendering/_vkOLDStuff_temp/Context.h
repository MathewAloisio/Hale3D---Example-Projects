/*----------------------------------/
/-------------Context---------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_CONTEXT
#define HALE3D_CONTEXT
#pragma once

/*Standard Includes*/
#include <array>
#include <string>
#include <stdexcept>
#include <unordered_map>

/*Hale3D Includes*/
#include "Tools.h"
#include "Pipeline.h"
#include "Frustum.h"
#include "Shader.h"
#include "GBuffer.h"
#include "Resources.h"
#include "Device.h"
#include "DeviceBuffer.h"
#include "../Libraries/System.h"
#include "../Structs/Matrix4.h"
#include "../Structs/ThreadPool.h"

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

/*Debugging Definition(s)*/
#define VK_CHECK_RESULT(RESULT)																											\
		if (RESULT != VK_SUCCESS) {																										\
			System::Print("\n[ERROR : Warning] Context returned error \"" + Tools::VkResultToString(RESULT) + "\".");					\
			System::Print("[ERROR TRACE] File: \"" + std::string(__FILE__) + "\" | Line: " + std::to_string(__LINE__) + "\n");			\
			throw std::runtime_error(Tools::VkResultToString(RESULT) + " " + std::string(__FILE__) + ":" + std::to_string(__LINE__));	\
		};		

namespace Hale3D {
	class Camera;
	class Window;
	class Swapchain;

	namespace DrawFlags {
		extern const uint32_t None;
		extern const uint32_t Wireframe;
	}

	class Context {
	public:
		Context(Window* pWindow);
		~Context();
		
		VkQueue queue;
		VkDescriptorPool descriptorPool;
		Frustum frustum;
		Resources resources;
		GBuffer* gBuffer = nullptr;

		void StartFrame(Camera* pCamera);
		void RenderFrame();
		//void Update(Camera* pCamera);
		void PrecacheEngineTextures();
		void HandleResize(int pWidth, int pHeight);
		void PrintVendorInfo();

		Window* GetWindow();
		Device* GetDevice();
		VkInstance& GetInstance();

		/*Dimensions*/
		uint32_t GetWidth();
		uint32_t GetHeight();

		/*FBOs/Images*/
		void SwapBuffers();
		void SetImageLayout(VkCommandBuffer pCMDBuffer, VkImage pImage, VkImageAspectFlags pAspect, VkImageLayout pOldLayout, VkImageLayout pNewLayout, VkImageSubresourceRange pSubresourceRange);

		/*Multithreading*/
		void SetupMultithreading();
		void DestroyMultithreading();
		ThreadPool& GetThreadPool();
		VkCommandPool GetThreadCommandPool(size_t pThreadIndex);

		/*Semaphores*/
		void CreateSemaphores();
		void DestroySemaphores();

		/*Multisampling*/
		void SetMSAA(int pSamples);
		int GetMSAA();
		VkSampleCountFlagBits GetMSAABits();

		/*Command Pools, Buffers & Inheritance*/
		VkCommandBuffer CreateCommandBuffer(VkCommandBufferLevel pLevel, bool pBegin);
		void CreateCommandPool();
		void DestroyCommandPool();
		void SubmitCommandBuffer(VkCommandBuffer& pCommandBuffer, VkCommandPool& pCommandPool);
		void ReserveCommandBufferSubmittions(size_t pCount);
		void FlushCommandBuffer(const VkCommandBuffer& pBuffer, VkQueue pQueue, bool pRelease);
		VkCommandBufferInheritanceInfo GenerateInheritanceInfo();
		VkCommandPool& GetCommandPool();

		/*Descriptor Pool*/
		void CreateDescriptorPool(uint32_t pMaxSets = 1);
		void DestroyDescriptorPool();

		/*Layouts & Descriptors*/
		void CreateLayoutsAndDescriptors();
		void DestroyLayoutsAndDescriptors();

		/*Uniform Buffers*/
		void CreateUBOs();
		void UpdateDeferredWorldUBO(void* pData, VkDeviceSize pSize);

		/*Pipelines*/
		void SetupPipelines();
		void DestroyPipelines();

		struct {
			Pipeline* solid = nullptr; //Opaque entities.
			Pipeline* blend = nullptr; //Translucent entities.
			Pipeline* wireframe = nullptr; //Wireframe.
		} pipelines;

		struct {
			PipelineLayout* deferred = nullptr;
		} pipelineLayouts;

		/*Special Features*/
		struct {
			bool AMDRasterizationOrder;
			bool NVDedicatedAllocation;
		} specialFeatures;

		/*Shaders*/
		VkShaderStageFlags shaderStageFlags = 0;

		/*Static Methods*/
		static void SetCurrent(Context* pContext);
		static Context* GetCurrent();

		static const VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	private:
		int msaaLevel = 0;
		uint32_t currentImage;
		Device* device;
		Window* window;
		Swapchain* swapchain;
		VkFormat depthFormat;
		VkInstance instance;
		VkSampler colorSampler;
		VkSurfaceKHR surface;
		VkFence renderFence;
		VkPipelineCache pipelineCache;
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> submittedCommandBuffers;
		std::vector<VkCommandPool> submittedCommandPools;

		struct {
			Shader* deferred;
			//Shader* skybox;
		} shaders;

		VkSubmitInfo submitInfo; //Frame submittion information.
		struct {
			VkSemaphore present;
			VkSemaphore render;
		} semaphores;

		/*Uniform Buffer Objects*/
		struct {
			struct { // Shader: deferred.
				struct {
					DeviceBuffer vertex;
				} world;
				
				struct {
					DeviceBuffer vertex;
					DeviceBuffer fragment;
				} entity;
			} deferred;
		} ubos;

		/*Multithreading*/
		struct {
			uint32_t availableThreads;
			ThreadPool threadPool;
			std::vector<VkCommandPool> threadCommandPools;
		} multithreading;
	};
}
#endif
