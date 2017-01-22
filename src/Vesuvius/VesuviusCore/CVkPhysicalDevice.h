#pragma once

#include "Vulkan.h"

<<<<<<< HEAD
=======
#include "CVkDevice.h"

#include <memory>
#include <vector>

>>>>>>> develop
namespace vesuvius
{
	class CVkPhysicalDevice
	{
	public:

		VkPhysicalDeviceProperties
<<<<<<< HEAD
		GetPhysicalDeviceProperties();
=======
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
>>>>>>> develop

	private:

		CVkPhysicalDevice(
<<<<<<< HEAD
			_In_ const VkPhysicalDevice& PhysicalDevice
=======
			_In_ const VkPhysicalDevice PhysicalDevice
>>>>>>> develop
		);

		VkPhysicalDevice m_physicalDevice;

		friend class CVkInstance;
	};
}