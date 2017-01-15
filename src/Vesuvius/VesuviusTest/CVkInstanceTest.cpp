#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{		
	TEST_CLASS(CVkInstanceTest)
	{
	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In CVkInstanceTest Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In CVkInstanceTest Class Cleanup");
		}
		
		TEST_METHOD(CreateInstance_Success)
		{
			(void)CreateInstance();
		}

		TEST_METHOD(EnumaratePhysicalDevices_Success)
		{
			VkResult result;

			std::shared_ptr<CVkInstance> instance =
				CreateInstance();

			std::vector<CVkPhysicalDevice> physicalDevices;
			result = instance->EnumeratePhysicalDevices(physicalDevices);
			
			Assert::AreEqual(result, VK_SUCCESS);
		}
	};
}