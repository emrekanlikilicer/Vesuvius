#pragma once

#include "Vulkan.h"
#include <vector>

namespace vesuvius
{
	class CVkPhysicalDevice
	{
	public:

		VkPhysicalDeviceProperties
		GetPhysicalDeviceProperties();
		
		VkResult
		GetPhysicalDeviceQueueFamilyProperties(
			_Out_ std::vector<VkQueueFamilyProperties>& QueueFamilyProperties
		);

	private:

		CVkPhysicalDevice(
			_In_ const VkPhysicalDevice& PhysicalDevice
		);

		VkPhysicalDevice m_physicalDevice;

		friend class CVkInstance;
	};
}