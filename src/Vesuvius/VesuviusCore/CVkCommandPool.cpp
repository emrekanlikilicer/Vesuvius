#include "CVkCommandPool.h"

using namespace vesuvius;

VkResult 
CVkCommandPool::Reset(_In_ VkCommandPoolResetFlags Flags)
{
	return vkResetCommandPool(m_device, m_commandPool, Flags);
}

CVkCommandPool::CVkCommandPool(
	_In_     VkDevice                   Device,
	_In_     VkCommandPool              CommandPool,
	_In_     VkCommandPoolCreateInfo    CommandPoolCreateInfo,
	_In_opt_ VkAllocationCallbacks*     AllocationCallbacks
):m_device(Device),
  m_commandPool(CommandPool),
  m_flags(CommandPoolCreateInfo.flags),
  m_queueFamilyIndex(CommandPoolCreateInfo.queueFamilyIndex)
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