#include "CVkPhysicalDevice.h"

using namespace vesuvius;

CVkPhysicalDevice::CVkPhysicalDevice(
	_In_ const VkPhysicalDevice PhysicalDevice
)
{
	m_physicalDevice = PhysicalDevice;
}

VkPhysicalDeviceProperties
CVkPhysicalDevice::GetPhysicalDeviceProperties() noexcept
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(m_physicalDevice, &properties);

	return properties;
}

VkResult 
CVkPhysicalDevice::GetPhysicalDeviceQueueFamilyProperties(
	_Out_ std::vector<VkQueueFamilyProperties>& QueueFamilyProperties
) noexcept
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

VkResult 
CVkPhysicalDevice::CreateDevice(
	_In_     const VkDeviceCreateInfo      DeviceCreateInfo,
	_In_opt_ const VkAllocationCallbacks * AllocationCallbacks,
	_Out_    std::shared_ptr<CVkDevice>&   Device
) noexcept
{
	Device.reset();

	VkDevice device;

	VkResult result = vkCreateDevice(
							m_physicalDevice, 
							&DeviceCreateInfo, 
							AllocationCallbacks,
							&device);
	if (result != VK_SUCCESS)
	{
		return result;
	}

	try
	{
		Device.reset(new CVkDevice(device, DeviceCreateInfo, AllocationCallbacks));
	}
	catch (std::bad_alloc&)
	{
		vkDestroyDevice(device, AllocationCallbacks);
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	return VK_SUCCESS;
}
