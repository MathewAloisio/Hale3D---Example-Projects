/*----------------------------------/
/-------------GBuffer---------------/
/-------Hale Game Engine 2016-------/
/----Copyright © Mathew Aloisio-----/
/----------------------------------*/
#ifndef HALE3D_GBUFFER
#define HALE3D_GBUFFER
#pragma once
/*Hale3D Include(s)*/
#include "Framebuffer.h"

/*Standard Include(s)*/
#include <array>

/*Include Vulkan*/
#include <vulkan/vulkan.hpp>

namespace Hale3D {
	class Context;

	class GBuffer {
	public:
		GBuffer(Context* pContext);
		~GBuffer();

		void Draw(const std::vector<VkCommandBuffer>& pSubBuffers);

		struct {
			Framebuffer* deferred;
		} fbos;

		std::array<VkClearValue, 4> clearValues;

	private:
		Context* context;
	};
}
#endif
