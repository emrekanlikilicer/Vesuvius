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