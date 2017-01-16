#pragma once

#include "Vulkan.h"

namespace vesuvius
{
	class CVkDevice
	{
	public:

		~CVkDevice();
	private:

		CVkDevice(
			_In_ const VkDevice device,
			_In_opt_ const VkAllocationCallbacks * AllocationCallbacks
		);

	private:

		VkDevice m_device;

		struct
		{
			VkAllocationCallbacks callbacks;
			bool                  useCallbacks;
		} m_AllocationCallbacks;

		friend class CVkPhysicalDevice;
	};
}