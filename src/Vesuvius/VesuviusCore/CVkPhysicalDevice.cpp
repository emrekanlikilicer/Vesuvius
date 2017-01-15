#include "CVkPhysicalDevice.h"

using namespace vesuvius;

CVkPhysicalDevice::CVkPhysicalDevice(
	_In_ const VkPhysicalDevice& PhysicalDevice
)
{
	m_physicalDevice = PhysicalDevice;
}

VkPhysicalDeviceProperties
CVkPhysicalDevice::GetPhysicalDeviceProperties()
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(m_physicalDevice, &properties);

	return properties;
}

VkResult 
CVkPhysicalDevice::GetPhysicalDeviceQueueFamilyProperties(
	_Out_ std::vector<VkQueueFamilyProperties>& QueueFamilyProperties)
{
	QueueFamilyProperties.clear();

	uint32_t queueCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueCount, NULL);
	if (queueCount == 0)
	{
		return VK_SUCCESS;
	}

	try
	{
		QueueFamilyProperties.resize(queueCount);
	}
	catch (std::bad_alloc)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, 
		                                     &queueCount,
											 QueueFamilyProperties.data());

	return VK_SUCCESS;
}
