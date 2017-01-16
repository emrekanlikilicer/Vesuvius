#include "CVkInstance.h"

using namespace vesuvius;

VkResult 
CVkInstance::CreateInstance(
	_In_     const VkInstanceCreateInfo&   CreateInstanceInfo, 
	_In_opt_ const VkAllocationCallbacks*  AllocationCallbacks,
	_Out_    std::shared_ptr<CVkInstance>& Instance
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

CVkInstance::CVkInstance()
{
	memset(&m_AllocationCallbacks, 0, sizeof(m_AllocationCallbacks));
	memset(&m_instance, 0, sizeof(m_instance));
}

CVkInstance::~CVkInstance()
{
	VkAllocationCallbacks* pCallbacks = NULL;

	if (m_AllocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_AllocationCallbacks.callbacks;
	}

	if (m_instance)
	{
		vkDestroyInstance(m_instance, pCallbacks);
	}
}

VkResult
CVkInstance::Create(
	_In_     const VkInstanceCreateInfo&  CreateInstanceInfo,
	_In_opt_ const VkAllocationCallbacks* AllocationCallbacks
)
{
	if (AllocationCallbacks != NULL)
	{
		m_AllocationCallbacks.callbacks    = *AllocationCallbacks;
		m_AllocationCallbacks.useCallbacks = true;
	}

	return vkCreateInstance(&CreateInstanceInfo, AllocationCallbacks, &m_instance);
}

VkResult
CVkInstance::EnumeratePhysicalDevices(
	_Out_ std::vector<CVkPhysicalDevice>&  PhysicalDevices
) noexcept
{
	PhysicalDevices.clear();

	std::vector<VkPhysicalDevice> physicalDeviceHandles;

	uint32_t count;
	VkResult result = vkEnumeratePhysicalDevices(m_instance, &count, NULL);
	if (result != VK_SUCCESS)
	{
		return result;
	}

	if (!count)
	{
		return VK_SUCCESS;
	}

	try
	{
		physicalDeviceHandles.resize(count);
	}
	catch (std::bad_alloc&)
	{
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	result = vkEnumeratePhysicalDevices(m_instance, &count, physicalDeviceHandles.data());

	try
	{
		for each (VkPhysicalDevice handle in physicalDeviceHandles)
		{
			PhysicalDevices.push_back(CVkPhysicalDevice(handle));
		}
	}
	catch (std::bad_alloc&)
	{
		result = VK_ERROR_OUT_OF_HOST_MEMORY;
		PhysicalDevices.clear();
	}

	return result;
}

