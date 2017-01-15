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
