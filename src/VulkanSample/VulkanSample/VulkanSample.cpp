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

void PrintPhysicalDeviceProperties(VkPhysicalDevice physicalDevice)
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(physicalDevice, &properties);

	cout << "Device name   : " << properties.deviceName << endl;
	cout << "Api version   : " << properties.apiVersion << endl;
	cout << "Driver version: " << properties.driverVersion << endl;
	cout << "Vendor Id     : " << properties.vendorID << endl;
	cout << "Device Id     : " << properties.deviceID << endl;
	cout << "Device Type   : " << properties.deviceType << endl;
	cout << endl;
}

bool GetQueueProperties(VkPhysicalDevice physicalDevice,
	std::vector<VkQueueFamilyProperties>& queueProperties
)
{
	uint32_t queueCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, NULL);
	if (queueCount == 0)
	{
		cout << "No queues found for the physical device" << endl;
		return false;
	}

	try
	{
		queueProperties.resize(queueCount);
	}
	catch (std::bad_alloc)
	{
		std::cerr << "Failed to allocate memory for queue properties" << std::endl;
		return false;
	}

	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueProperties.data());

	return true;
}

bool ChoosePrimaryPhysicalDevice(const std::vector<VkPhysicalDevice> physicalDevices,
	VkPhysicalDevice& primaryPhysicalDevice)
{
	// Find a device that has graphics and compute queues. Choose discrete device over
	// integrated.
	
	std::vector<VkPhysicalDevice> candidates;

	for each (VkPhysicalDevice physicalDevice in physicalDevices)
	{
		std::vector<VkQueueFamilyProperties> queueProperties;
		if (!GetQueueProperties(physicalDevice, queueProperties))
		{
			continue;
		}

		bool deviceFound = false;
		for each(VkQueueFamilyProperties queueProperty in queueProperties)
		{
			if ((queueProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				(queueProperty.queueFlags & VK_QUEUE_COMPUTE_BIT))
			{
				deviceFound = true;
			}
		}

		if (!deviceFound)
		{
			continue;
		}

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(physicalDevice, &properties);
		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			candidates.insert(candidates.begin(), physicalDevice);
		}
		else
		{
			candidates.push_back(physicalDevice);
		}
	}

	if (candidates.empty())
	{
		return false;
	}

	primaryPhysicalDevice = candidates[0];
	return true;
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

	for each (auto physicalDevice in physicalDevices)
	{
		PrintPhysicalDeviceProperties(physicalDevice);

		std::vector<VkQueueFamilyProperties> queueProperties;
		GetQueueProperties(physicalDevice, queueProperties);

		for each (auto queueProperty in queueProperties)
		{
			cout << "Physical device queue information" << endl;
			cout << "Queue Flags: " << queueProperty.queueFlags << endl;
			cout << "Queue Count: " << queueProperty.queueCount << endl;
			cout << "Queue Min Image Transfer Width:" << queueProperty.minImageTransferGranularity.width << endl;
			cout << "Queue Min Image Transfer Height:" << queueProperty.minImageTransferGranularity.height << endl;
			cout << "Queue Min Image Transfer Depth:" << queueProperty.minImageTransferGranularity.depth << endl;
			cout << endl;
		}
	}

	VkPhysicalDevice primaryPhysicalDevice; 
	if (!ChoosePrimaryPhysicalDevice(physicalDevices, primaryPhysicalDevice))
	{
		cout << "Pimary device is not found." << endl;
		return 0;
	}
	else
	{
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(primaryPhysicalDevice, &props);
		cout << "Primary device found : " << props.deviceName << endl;
	}

	

	//
	// Terminate the application
	//
	vkDestroyInstance(instance, NULL);
	
	cout << "Program completed successfully" << endl;

    return 0;
}

