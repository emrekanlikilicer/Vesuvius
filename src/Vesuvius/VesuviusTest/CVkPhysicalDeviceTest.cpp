#include "stdafx.h"
#include "CppUnitTest.h"
#include "CVkInstance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{
	TEST_CLASS(CVkPhysicalDeviceTest)
	{
<<<<<<< HEAD
=======
	private:
		static std::shared_ptr<CVkInstance>   m_instance;
		static std::vector<CVkPhysicalDevice> m_physicalDevices;

>>>>>>> develop
	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
<<<<<<< HEAD
			Logger::WriteMessage("In CVkPhysicalDeviceTest Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In CVkPhysicalDeviceTest Class Cleanup");
=======
			m_instance = CreateInstance();
			Assert::IsNotNull(m_instance.get());

			VkResult result = m_instance->EnumeratePhysicalDevices(m_physicalDevices);
			Assert::AreEqual(result, VK_SUCCESS);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			m_physicalDevices.clear();
			m_instance.reset();
>>>>>>> develop
		}

		TEST_METHOD(GetPhysicalDeviceProperties_Success)
		{
<<<<<<< HEAD
			VkResult result;
			std::shared_ptr<CVkInstance> instance =
				CreateInstance();

			std::vector<CVkPhysicalDevice> physicalDevices;
			result = instance->EnumeratePhysicalDevices(physicalDevices);

			Assert::AreEqual(result, VK_SUCCESS);

			for each(CVkPhysicalDevice physicalDevice in physicalDevices)
			{
				VkPhysicalDeviceProperties properties = 
				physicalDevice.GetPhysicalDeviceProperties();

				Logger::WriteMessage(properties.deviceName);
=======
			for each(CVkPhysicalDevice physicalDevice in m_physicalDevices)
			{
				VkPhysicalDeviceProperties properties;
				memset(&properties, 0, sizeof(properties));

				properties = physicalDevice.GetPhysicalDeviceProperties();

				Assert::IsNotNull(properties.deviceName);
				Assert::IsTrue(properties.vendorID > 0);
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

				VkResult result =  physicalDevice.CreateDevice(deviceCreateInfo,
																NULL,
																device);
				Assert::AreEqual(result, VK_SUCCESS);
				Assert::IsNotNull(device.get());
>>>>>>> develop
			}
		}

	};
<<<<<<< HEAD
=======

	std::shared_ptr<CVkInstance>   CVkPhysicalDeviceTest::m_instance;
	std::vector<CVkPhysicalDevice> CVkPhysicalDeviceTest::m_physicalDevices;

>>>>>>> develop
}