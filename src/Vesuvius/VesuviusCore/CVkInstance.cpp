#include "CVkInstance.h"

VkResult 
vesuvius::CVkInstance::CreateInstance(
	_In_  const VkInstanceCreateInfo&   CreateInstanceInfo, 
	_In_ const VkAllocationCallbacks&   AllocationCallbacks,
	_Out_ std::shared_ptr<CVkInstance>& Instance
) noexcept
{
	VkResult result = VK_ERROR_INITIALIZATION_FAILED;

	try
	{
		Instance.reset(new CVkInstance());
	}
	catch (std::bad_alloc&)
	{
		result = VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	if (Instance)
	{
		result = Instance->Create(CreateInstanceInfo, AllocationCallbacks);
		if (result != VK_SUCCESS)
		{
			Instance.reset();
		}
	}

	return result;
}

VkResult 
vesuvius::CVkInstance::Create(
	_In_ const VkInstanceCreateInfo&  CreateInstanceInfo,
	_In_ const VkAllocationCallbacks& AllocationCallbacks
)
{
	return vkCreateInstance(&CreateInstanceInfo, &AllocationCallbacks, &m_instance);
}
