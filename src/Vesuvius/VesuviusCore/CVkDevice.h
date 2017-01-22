#pragma once

#include "Vulkan.h"

#include "CVkQueue.h"
#include "CVkCommandPool.h"

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
		CreateCommandPool(
			_In_     VkCommandPoolCreateInfo          CommandPoolCreateInfo,
			_In_opt_ VkAllocationCallbacks*           AllocationCallbacks,
			_Out_    std::shared_ptr<CVkCommandPool>& CommandPool
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

		std::weak_ptr<CVkDevice> m_thisWeakPtr;

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