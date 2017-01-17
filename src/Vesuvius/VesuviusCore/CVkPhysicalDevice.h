#pragma once

#include "Vulkan.h"
#include "CVkDevice.h"
#include <vector>
#include <memory>

namespace vesuvius
{
	class CVkPhysicalDevice
	{
	public:

		VkPhysicalDeviceProperties
		GetPhysicalDeviceProperties() noexcept;
		
		VkResult
		GetPhysicalDeviceQueueFamilyProperties(
			_Out_ std::vector<VkQueueFamilyProperties>& QueueFamilyProperties
		) noexcept;

		VkResult
		CreateDevice(
			_In_      const VkDeviceCreateInfo      DeviceCreateInfo,
			_In_opt_  const VkAllocationCallbacks*  AllocationCallbacks,
			_Out_     std::shared_ptr<CVkDevice>&   Device
		) noexcept;

	private:

		CVkPhysicalDevice(
			_In_ const VkPhysicalDevice PhysicalDevice
		);

		VkPhysicalDevice m_physicalDevice;

		friend class CVkInstance;
	};
}