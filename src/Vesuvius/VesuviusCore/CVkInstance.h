#pragma once

#include "Vulkan.h"

#include "CVkPhysicalDevice.h"

#include <memory>
#include <vector>

namespace vesuvius
{
	class CVkInstance
	{
	public:
		//
		// Creates an CVkInstance object.	
		//
		static VkResult
		CreateInstance(
			_In_     const VkInstanceCreateInfo&    CreateInstanceInfo,
			_In_opt_ const VkAllocationCallbacks*   AllocationCallbacks,
			_Out_    std::shared_ptr<CVkInstance>&  Instance
		) noexcept;

		//
		// Enumerates the physical devices accessible to a Vulkan instance
		//
		VkResult
		EnumeratePhysicalDevices(
			_Out_ std::vector<CVkPhysicalDevice>&  PhysicalDevices
		) noexcept;

		~CVkInstance();

	private:
		CVkInstance();
		CVkInstance(const CVkInstance&);
		CVkInstance& operator=(const CVkInstance&);

		VkResult
		Create(
			_In_     const VkInstanceCreateInfo&  CreateInstanceInfo,
			_In_opt_ const VkAllocationCallbacks* AllocationCallbacks
		);

	private:
		VkInstance m_instance;

		struct
		{
			VkAllocationCallbacks callbacks;
			bool                  useCallbacks;
		} m_allocationCallbacks;
	};
}
