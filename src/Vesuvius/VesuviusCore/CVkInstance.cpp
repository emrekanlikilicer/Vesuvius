#include "CVkInstance.h"

<<<<<<< HEAD
VkResult 
vesuvius::CVkInstance::CreateInstance(
=======
using namespace vesuvius;

VkResult 
CVkInstance::CreateInstance(
>>>>>>> develop
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

<<<<<<< HEAD
vesuvius::CVkInstance::CVkInstance()
{
	memset(&m_AllocationCallbacks, 0, sizeof(m_AllocationCallbacks));
	memset(&m_instance, 0, sizeof(m_instance));
}

vesuvius::CVkInstance::~CVkInstance()
{
	VkAllocationCallbacks* pCallbacks = NULL;

	if (m_AllocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_AllocationCallbacks.callbacks;
=======
CVkInstance::CVkInstance()
{
	memset(&m_allocationCallbacks, 0, sizeof(m_allocationCallbacks));
	memset(&m_instance, 0, sizeof(m_instance));
}

CVkInstance::~CVkInstance()
{
	VkAllocationCallbacks* pCallbacks = NULL;

	if (m_allocationCallbacks.useCallbacks)
	{
		pCallbacks = &m_allocationCallbacks.callbacks;
>>>>>>> develop
	}

	if (m_instance)
	{
		vkDestroyInstance(m_instance, pCallbacks);
	}
}

VkResult
<<<<<<< HEAD
vesuvius::CVkInstance::Create(
=======
CVkInstance::Create(
>>>>>>> develop
	_In_     const VkInstanceCreateInfo&  CreateInstanceInfo,
	_In_opt_ const VkAllocationCallbacks* AllocationCallbacks
)
{
	if (AllocationCallbacks != NULL)
	{
<<<<<<< HEAD
		m_AllocationCallbacks.callbacks    = *AllocationCallbacks;
		m_AllocationCallbacks.useCallbacks = true;
=======
		m_allocationCallbacks.callbacks    = *AllocationCallbacks;
		m_allocationCallbacks.useCallbacks = true;
>>>>>>> develop
	}

	return vkCreateInstance(&CreateInstanceInfo, AllocationCallbacks, &m_instance);
}

VkResult
<<<<<<< HEAD
vesuvius::CVkInstance::EnumeratePhysicalDevices(
=======
CVkInstance::EnumeratePhysicalDevices(
>>>>>>> develop
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
<<<<<<< HEAD
=======

>>>>>>> develop
