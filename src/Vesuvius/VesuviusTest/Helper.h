#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

inline std::shared_ptr<vesuvius::CVkInstance>
CreateInstance()
{
	std::shared_ptr<vesuvius::CVkInstance> instance;

	VkInstanceCreateInfo createInfo;
	memset(&createInfo, 0, sizeof(createInfo));

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	VkResult result =
		vesuvius::CVkInstance::CreateInstance(createInfo, NULL, instance);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(result, VK_SUCCESS);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(instance.get());

	return instance;
}


inline std::shared_ptr<vesuvius::CVkDevice>
CreateDevice(_In_ std::shared_ptr<vesuvius::CVkInstance> instance)
{
	std::vector<vesuvius::CVkPhysicalDevice> physicalDevices;
	VkResult result = instance->EnumeratePhysicalDevices(physicalDevices);
	Assert::AreEqual(result, VK_SUCCESS);

	if (physicalDevices.empty())
		return NULL;

	// choose the first physical device in the list
	VkDeviceCreateInfo deviceInfo;
	memset(&deviceInfo, 0, sizeof(deviceInfo));
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.queueCreateInfoCount = 1;

	VkDeviceQueueCreateInfo queueInfo;
	memset(&queueInfo, 0, sizeof(queueInfo));
	queueInfo.queueCount = 1;
	queueInfo.queueFamilyIndex = 0;
	queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	
	deviceInfo.pQueueCreateInfos = &queueInfo;

	std::shared_ptr<vesuvius::CVkDevice> device;
	result = physicalDevices[0].CreateDevice(deviceInfo, NULL, device);
	
	Assert::AreEqual(result, VK_SUCCESS);
	Assert::IsNotNull(device.get());

	return device;
}
