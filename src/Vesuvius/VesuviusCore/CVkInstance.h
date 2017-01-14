#pragma once

#include "Vulkan.h"
#include <memory>

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
			_In_ const VkInstanceCreateInfo&     CreateInstanceInfo,
			_In_ const VkAllocationCallbacks&    AllocationCallbacks,
			_Out_ std::shared_ptr<CVkInstance>&  Instance
		) noexcept;
		
	private:
		CVkInstance();

		VkResult
		Create(
			_In_ const VkInstanceCreateInfo&  CreateInstanceInfo,
			_In_ const VkAllocationCallbacks& AllocationCallbacks
		);

	private:
		VkInstance m_instance;
	};
}
