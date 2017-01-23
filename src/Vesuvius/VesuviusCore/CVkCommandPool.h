#pragma once

#include "Vulkan.h"

#include "CVkCommandBuffer.h"

#include <memory>
#include <vector>

namespace vesuvius
{
	class CVkCommandPool
	{
	public:

		VkResult 
		Reset(_In_ VkCommandPoolResetFlags Flags) noexcept;

		void
		Destroy() noexcept;

		VkResult
		AllocateCommandBuffers(
			_In_  VkCommandBufferLevel                            CommandBufferLevel,
			_In_  uint32_t                                        CommandBufferCount,
			_Out_ std::vector<std::shared_ptr<CVkCommandBuffer>>& CommandBuffers
		) noexcept;

		~CVkCommandPool();

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

		bool m_destroyed;
	};
}