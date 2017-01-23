#include "CVkCommandPool.h"

using namespace vesuvius;

VkResult 
CVkCommandPool::Reset(_In_ VkCommandPoolResetFlags Flags) noexcept
{
	return vkResetCommandPool(m_device, m_commandPool, Flags);
}

void 
CVkCommandPool::Destroy() noexcept
{
	if (m_destroyed)
	{
		return;
	}

	m_destroyed = true;

	VkAllocationCallbacks* pCallbacks = NULL;
	if (m_allocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_allocationCallbacks.callbacks;
	}

	vkDestroyCommandPool(m_device, m_commandPool, pCallbacks);
}

VkResult 
CVkCommandPool::AllocateCommandBuffers(
	_In_  VkCommandBufferLevel                            CommandBufferLevel,
	_In_  uint32_t                                        CommandBufferCount,
	_Out_ std::vector<std::shared_ptr<CVkCommandBuffer>>& CommandBuffers) noexcept
{
	CommandBuffers.clear();

	if (CommandBufferCount == 0)
	{
		return VK_SUCCESS;
	}

	VkCommandBufferAllocateInfo allocateInfo;
	memset(&allocateInfo, 0, sizeof(allocateInfo));

	std::vector<VkCommandBuffer> handles;
	try
	{
		handles.resize(CommandBufferCount);
	}
	catch (std::bad_alloc&)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	allocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandBufferCount = CommandBufferCount;
	allocateInfo.level              = CommandBufferLevel;
	allocateInfo.commandPool        = m_commandPool;

	VkResult result = 
		vkAllocateCommandBuffers(m_device, &allocateInfo, handles.data());

	if (result != VK_SUCCESS)
	{
		return result;
	}

	try
	{
		auto it = handles.begin();
		while (it != handles.end())
		{
			std::shared_ptr<CVkCommandBuffer> commandBuffer;
			commandBuffer.reset(new CVkCommandBuffer(*it, m_device, m_commandPool));
			
			it = handles.erase(it);
			CommandBuffers.push_back(commandBuffer);
		}
	}
	catch (std::bad_alloc)
	{
		if (!handles.empty())
		{
			vkFreeCommandBuffers(m_device, m_commandPool, (uint32_t)handles.size(), handles.data());
		}
		CommandBuffers.clear();

		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

CVkCommandPool::~CVkCommandPool()
{
	Destroy();
}

CVkCommandPool::CVkCommandPool(
	_In_     VkDevice                   Device,
	_In_     VkCommandPool              CommandPool,
	_In_     VkCommandPoolCreateInfo    CommandPoolCreateInfo,
	_In_opt_ VkAllocationCallbacks*     AllocationCallbacks
) :m_device(Device),
m_commandPool(CommandPool),
m_flags(CommandPoolCreateInfo.flags),
m_queueFamilyIndex(CommandPoolCreateInfo.queueFamilyIndex),
m_destroyed(false)
{
	if (AllocationCallbacks)
	{
		m_allocationCallbacks.callbacks = *AllocationCallbacks;
		m_allocationCallbacks.useCallbacks = true;
	}
	else
	{
		memset(&m_allocationCallbacks, 0, sizeof(m_allocationCallbacks));
	}
}