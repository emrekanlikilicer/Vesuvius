#pragma once

#include "Vulkan.h"
#include <vector>

namespace vesuvius
{
	class CVkDevice
	{
	public:

		~CVkDevice();

		VkResult 
		WaitIdle() noexcept;

	private:

		CVkDevice(
			_In_ const VkDevice device,
			_In_     const VkDeviceCreateInfo      DeviceCreateInfo,
			_In_opt_ const VkAllocationCallbacks * AllocationCallbacks
		);

	private:

		VkDevice m_device;

		struct
		{
			VkAllocationCallbacks callbacks;
			bool                  useCallbacks;
		} m_allocationCallbacks;

		struct QueueProperties
		{
			VkDeviceQueueCreateFlags    flags;
			uint32_t                    queueFamilyIndex;
			uint32_t                    queueCount;
		};

		std::vector<QueueProperties> m_queueCreateInfos;

		friend class CVkPhysicalDevice;
	};
}