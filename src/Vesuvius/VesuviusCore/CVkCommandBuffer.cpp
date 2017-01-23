#include "CVkCommandBuffer.h"

using namespace vesuvius;

CVkCommandBuffer::~CVkCommandBuffer()
{
	Free();
}

CVkCommandBuffer::CVkCommandBuffer(
	_In_ VkCommandBuffer CommandBuffer, 
	_In_ VkDevice        Device, 
	_In_ VkCommandPool   CommandPool
): m_commandBuffer(CommandBuffer),
   m_device(Device),
   m_commandPool(CommandPool),
   m_freed(false)
{
}

void 
CVkCommandBuffer::Free() noexcept
{
	if (m_freed)
	{
		return;
	}
	m_freed = true;
	vkFreeCommandBuffers(m_device, m_commandPool, 1, &m_commandBuffer);
}


VkResult
CVkCommandBuffer::Reset(_In_ VkCommandBufferResetFlags Flags) noexcept
{
	return vkResetCommandBuffer(m_commandBuffer, Flags);
}

VkResult
CVkCommandBuffer::Begin(
	_In_ VkCommandBufferUsageFlags     Flags,
	_In_ VkRenderPass                  RenderPass,
	_In_ uint32_t                      Subpass,
	_In_ VkFramebuffer                 FrameBuffer,
	_In_ VkBool32                      OcclusionQueryEnable,
	_In_ VkQueryControlFlags           QueryFlags,
	_In_ VkQueryPipelineStatisticFlags PipelineStatistics
) noexcept
{
	VkCommandBufferBeginInfo beginInfo;
	memset(&beginInfo, 0, sizeof(beginInfo));

	VkCommandBufferInheritanceInfo inheritanceInfo;
	memset(&inheritanceInfo, 0, sizeof(inheritanceInfo));

	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = Flags;
	beginInfo.pInheritanceInfo = &inheritanceInfo;

	inheritanceInfo.framebuffer = FrameBuffer;
	inheritanceInfo.occlusionQueryEnable = OcclusionQueryEnable;
	inheritanceInfo.pipelineStatistics = PipelineStatistics;
	inheritanceInfo.queryFlags = QueryFlags;
	inheritanceInfo.renderPass = RenderPass;
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.subpass = Subpass;

	return vkBeginCommandBuffer(m_commandBuffer, &beginInfo);
}

VkResult
CVkCommandBuffer::Begin(_In_ VkCommandBufferUsageFlags Flags) noexcept
{
	VkCommandBufferBeginInfo beginInfo;
	memset(&beginInfo, 0, sizeof(beginInfo));

	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = Flags;

	return vkBeginCommandBuffer(m_commandBuffer, &beginInfo);
}

VkResult
CVkCommandBuffer::End() noexcept
{
	return vkEndCommandBuffer(m_commandBuffer);
}