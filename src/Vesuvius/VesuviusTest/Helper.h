#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

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
