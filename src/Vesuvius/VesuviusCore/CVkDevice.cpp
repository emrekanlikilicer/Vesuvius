#include "CVkDevice.h"
#include <memory>

using namespace vesuvius;

CVkDevice::~CVkDevice()
{
	VkAllocationCallbacks* pCallbacks = NULL;

	if (m_allocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_allocationCallbacks.callbacks;
	}
	vkDestroyDevice(m_device, pCallbacks);
}

VkResult 
CVkDevice::GetQueue(
	_In_  uint32_t QueueFamilyIndex, 
	_In_  uint32_t QueueIndex, 
	_Out_ std::shared_ptr<CVkQueue>& Queue
) noexcept
{
	VkQueue queue;
	vkGetDeviceQueue(m_device,
		QueueFamilyIndex,
		QueueIndex,
		&queue);

	try
	{
		Queue.reset(new CVkQueue(queue, QueueFamilyIndex, QueueIndex));
	}
	catch (std::bad_alloc&)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VkResult 
CVkDevice::CreateCommandPool(
	_In_     VkCommandPoolCreateInfo          CommandPoolCreateInfo,
	_In_opt_ VkAllocationCallbacks*           AllocationCallbacks,
	_Out_    std::shared_ptr<CVkCommandPool>& CommandPool
) noexcept
{
	CommandPool.reset();

	VkCommandPool commandPool;

	VkResult result = vkCreateCommandPool(m_device, 
		                                  &CommandPoolCreateInfo,
		                                  AllocationCallbacks,
		                                  &commandPool );
	if (result != VK_SUCCESS)
	{
		return result;
	}

	try
	{
		CommandPool.reset(new CVkCommandPool(m_device,
			commandPool,
			CommandPoolCreateInfo,
			AllocationCallbacks));
	}
	catch (std::bad_alloc&)
	{
		vkDestroyCommandPool(m_device, commandPool, AllocationCallbacks);
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}

VkResult 
CVkDevice::WaitIdle() noexcept
{
	return vkDeviceWaitIdle(m_device);
}

CVkDevice::CVkDevice(
	_In_     const VkDevice                Device,
	_In_     const VkDeviceCreateInfo      DeviceCreateInfo,
	_In_opt_ const VkAllocationCallbacks * AllocationCallbacks
)
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

	for (uint32_t i = 0; i < DeviceCreateInfo.queueCreateInfoCount; i++)
	{
		try
		{
			QueueProperties queueProperties;
			queueProperties.flags      = DeviceCreateInfo.pQueueCreateInfos[i].flags;
			queueProperties.queueCount = DeviceCreateInfo.pQueueCreateInfos[i].queueCount;
			queueProperties.queueFamilyIndex = DeviceCreateInfo.pQueueCreateInfos[i].queueFamilyIndex;

			m_queueCreateInfos.push_back(queueProperties);
		}
		catch (std::bad_alloc& ex)
		{
			throw ex;
		}
	}

	m_device = Device;
}
