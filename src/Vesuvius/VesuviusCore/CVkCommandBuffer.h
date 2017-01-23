#pragma once

#include "Vulkan.h"
#include <vector>

namespace vesuvius
{
	class CVkCommandBuffer
	{
	public:

		~CVkCommandBuffer();

		void 
		Free() noexcept;

		VkResult
		Reset(_In_ VkCommandBufferResetFlags Flags) noexcept;


		VkResult
		Begin(_In_ VkCommandBufferUsageFlags Flags) noexcept;

		VkResult
		Begin(
			_In_ VkCommandBufferUsageFlags     Flags,
			_In_ VkRenderPass                  RenderPass,
			_In_ uint32_t                      Subpass,
			_In_ VkFramebuffer                 FrameBuffer,
			_In_ VkBool32                      OcclusionQueryEnable,
			_In_ VkQueryControlFlags           QueryFlags,
			_In_ VkQueryPipelineStatisticFlags PipelineStatistics
		) noexcept;

		VkResult
		End() noexcept;

	private:
		friend class CVkCommandPool;

	private:

		CVkCommandBuffer(
			_In_ VkCommandBuffer CommandBuffer,
			_In_ VkDevice        Device,
			_In_ VkCommandPool   CommandPool
		);

		CVkCommandBuffer(const CVkCommandBuffer&);
		CVkCommandBuffer& operator=(const  CVkCommandBuffer&);

		VkCommandBuffer m_commandBuffer;
		VkCommandPool   m_commandPool;
		VkDevice        m_device;

		bool m_freed;
	};
}