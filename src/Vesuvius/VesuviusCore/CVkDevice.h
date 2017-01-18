#pragma once

#include "Vulkan.h"

#include "CVkQueue.h"

#include <memory>
#include <vector>

namespace vesuvius
{
	class CVkDevice
	{
	public:

		~CVkDevice();

		VkResult
		GetQueue(
			_In_  uint32_t                    QueueFamilyIndex,
			_In_  uint32_t                    QueueIndex,
			_Out_ std::shared_ptr<CVkQueue>&  Queue
		) noexcept;

		VkResult 
		WaitIdle() noexcept;

	private:

		CVkDevice(
			_In_ const VkDevice device,
			_In_     const VkDeviceCreateInfo      DeviceCreateInfo,
			_In_opt_ const VkAllocationCallbacks * AllocationCallbacks
		);

		CVkDevice(const CVkDevice&);
		CVkDevice& operator=(const  CVkDevice&);

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