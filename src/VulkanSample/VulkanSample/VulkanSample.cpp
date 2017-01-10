// VulkanSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include  "vulkan.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

VkResult CreateVkInstance(VkInstance& instance)
{
	VkInstanceCreateInfo instanceCreateInfo;
	memset(&instanceCreateInfo, 0, sizeof(instanceCreateInfo));

	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	VkResult result = vkCreateInstance(&instanceCreateInfo, NULL, &instance);
	if (result != VK_SUCCESS)
	{
		cout << "vkCreateInstance: " << result << endl;
	}
	return result;
}

VkResult GetPhysicalDevices(
	VkInstance&                    instance,
	std::vector<VkPhysicalDevice>& physicalDevices)
{
	physicalDevices.clear();

	uint32_t count;
	VkResult result = vkEnumeratePhysicalDevices(instance, &count, NULL);
	if (result != VK_SUCCESS)
	{
		cout << "vkEnumeratePhysicalDevices: " << result << endl;
		return result;
	}

	cout << "Number of physical devices: " << count << endl;
	if (!count)
	{
		return VK_SUCCESS;
	}

	try
	{
		physicalDevices.resize(count);
	}
	catch (std::bad_alloc&)
	{
		std::cerr << "Failed to allocate memory for physical devices" << std::endl;
		return VK_ERROR_OUT_OF_HOST_MEMORY;
	}

	result = vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data());
	if (result != VK_SUCCESS)
	{
		cout << "vkEnumeratePhysicalDevices: " << result << endl;
	}

	return result;
}


int main()
{
	//
	// Create an VkInstance
	//
	VkInstance instance;
	if (VK_SUCCESS != CreateVkInstance(instance))
	{
		return -1;
	}

	//
	// Enumarate Physical Devices
	//
	std::vector<VkPhysicalDevice> physicalDevices;
	if (VK_SUCCESS != GetPhysicalDevices(instance, physicalDevices))
	{
		return -1;
	}

	//
	// Terminate the application
	//
	vkDestroyInstance(instance, NULL);
	
	cout << "Program completed successfully" << endl;

    return 0;
}

