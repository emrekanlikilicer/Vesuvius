#include "CVkDevice.h"
#include <memory>

using namespace vesuvius;

CVkDevice::~CVkDevice()
{
	VkAllocationCallbacks* pCallbacks = NULL;

	if (m_AllocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_AllocationCallbacks.callbacks;
	}
	vkDestroyDevice(m_device, pCallbacks);
}

CVkDevice::CVkDevice(
	_In_     const VkDevice                Device,
	_In_opt_ const VkAllocationCallbacks * AllocationCallbacks
)
{
	m_device = Device;

	if (AllocationCallbacks)
	{
		m_AllocationCallbacks.callbacks = *AllocationCallbacks;
		m_AllocationCallbacks.useCallbacks = true;
	}
	else
	{
		memset(&m_AllocationCallbacks, 0, sizeof(m_AllocationCallbacks));
	}
}