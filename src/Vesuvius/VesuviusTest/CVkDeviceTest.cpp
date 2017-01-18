#include "stdafx.h"
#include "CppUnitTest.h"
#include "CVkInstance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{
	TEST_CLASS(CVkDeviceTest)
	{
	private:
		static std::shared_ptr<CVkInstance>   m_instance;
		static std::vector<CVkPhysicalDevice> m_physicalDevices;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			m_instance = CreateInstance();
			Assert::IsNotNull(m_instance.get());

			VkResult result = m_instance->EnumeratePhysicalDevices(m_physicalDevices);
			Assert::AreEqual(result, VK_SUCCESS);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			m_physicalDevices.clear();
			m_instance.reset();
		}

		TEST_METHOD(GetQueue_Success)
		{
			for each(CVkPhysicalDevice physicalDevice in m_physicalDevices)
			{
				std::vector<VkQueueFamilyProperties> properties;
				VkResult result = physicalDevice.GetPhysicalDeviceQueueFamilyProperties(properties);
				Assert::AreEqual(result, VK_SUCCESS);

				for (int i = 0; i < properties.size(); i++)
				{
					for (uint32_t queueCount = 1; queueCount <= properties[i].queueCount; queueCount++)
					{
						std::shared_ptr<CVkDevice> device;

						VkDeviceCreateInfo deviceCreateInfo;
						VkDeviceQueueCreateInfo deviceQueueCreateInfo;

						memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
						memset(&deviceQueueCreateInfo, 0, sizeof(deviceQueueCreateInfo));

						deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
						deviceQueueCreateInfo.queueCount = queueCount;
						deviceQueueCreateInfo.queueFamilyIndex = i;

						deviceCreateInfo.queueCreateInfoCount = 1;
						deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

						VkResult result = physicalDevice.CreateDevice(deviceCreateInfo,
							NULL,
							device);
						Assert::AreEqual(result, VK_SUCCESS);
						Assert::IsNotNull(device.get());

						for (uint32_t queueIndex = 0; queueIndex < queueCount; queueIndex++)
						{
							std::shared_ptr<CVkQueue> queue;
							result = device->GetQueue(i, queueCount - 1, queue);

							Assert::AreEqual(result, VK_SUCCESS);
							Assert::IsNotNull(queue.get());
						}

						result = device->WaitIdle();
						Assert::AreEqual(result, VK_SUCCESS);
					}
				}

			}
		}

		TEST_METHOD(GetPhysicalDeviceQueueFamilyProperties_Success)
		{
			for each(CVkPhysicalDevice physicalDevice in m_physicalDevices)
			{
				std::vector<VkQueueFamilyProperties> properties;
				VkResult result = physicalDevice.GetPhysicalDeviceQueueFamilyProperties(properties);

				Assert::AreEqual(result, VK_SUCCESS);
				Assert::IsTrue(properties.size() > 0);
			}
		}

		TEST_METHOD(CreateDevice_Success)
		{
			for each(CVkPhysicalDevice physicalDevice in m_physicalDevices)
			{
				std::shared_ptr<CVkDevice> device;

				VkDeviceCreateInfo deviceCreateInfo;
				VkDeviceQueueCreateInfo deviceQueueCreateInfo;

				memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
				memset(&deviceQueueCreateInfo, 0, sizeof(deviceQueueCreateInfo));

				deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				deviceQueueCreateInfo.queueCount = 1;
				deviceQueueCreateInfo.queueFamilyIndex = 0;

				deviceCreateInfo.queueCreateInfoCount = 1;
				deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

				VkResult result = physicalDevice.CreateDevice(deviceCreateInfo,
					NULL,
					device);
				Assert::AreEqual(result, VK_SUCCESS);
				Assert::IsNotNull(device.get());
			}
		}

	};

	std::shared_ptr<CVkInstance>   CVkDeviceTest::m_instance;
	std::vector<CVkPhysicalDevice> CVkDeviceTest::m_physicalDevices;
}