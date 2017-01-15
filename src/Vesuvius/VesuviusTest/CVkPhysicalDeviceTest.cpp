#include "stdafx.h"
#include "CppUnitTest.h"
#include "CVkInstance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{
	TEST_CLASS(CVkPhysicalDeviceTest)
	{
	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In CVkPhysicalDeviceTest Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In CVkPhysicalDeviceTest Class Cleanup");
		}

		TEST_METHOD(GetPhysicalDeviceProperties_Success)
		{
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
			}
		}

	};
}