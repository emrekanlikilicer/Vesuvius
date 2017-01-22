#pragma once

#include "Vulkan.h"
#include <memory>

namespace vesuvius
{
	class CVkCommandPool
	{
	public:

		VkResult 
		Reset(_In_ VkCommandPoolResetFlags Flags);

	private:
		friend class CVkDevice;

	private:

		CVkCommandPool(
			_In_     VkDevice                   Device,
			_In_     VkCommandPool              CommandPool,
			_In_     VkCommandPoolCreateInfo    CommandPoolCreateInfo,
			_In_opt_ VkAllocationCallbacks*     AllocationCallbacks
		);

		CVkCommandPool(const CVkCommandPool&);
		CVkCommandPool& operator=(const  CVkCommandPool&);

		VkCommandPool              m_commandPool;
		VkDevice                   m_device;

		uint32_t                   m_queueFamilyIndex;
		VkCommandPoolCreateFlags   m_flags;


		struct
		{
			VkAllocationCallbacks callbacks;
			bool                  useCallbacks;
		} m_allocationCallbacks;
	};
}