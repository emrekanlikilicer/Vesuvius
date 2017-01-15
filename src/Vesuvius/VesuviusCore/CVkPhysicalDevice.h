#pragma once

#include "Vulkan.h"

namespace vesuvius
{
	class CVkPhysicalDevice
	{
	public:

		VkPhysicalDeviceProperties
		GetPhysicalDeviceProperties();

	private:

		CVkPhysicalDevice(
			_In_ const VkPhysicalDevice& PhysicalDevice
		);

		VkPhysicalDevice m_physicalDevice;

		friend class CVkInstance;
	};
}