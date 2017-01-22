#include "stdafx.h"
#include "CppUnitTest.h"
#include "CVkInstance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{
	TEST_CLASS(CVkCommandPoolTest)
	{
	private:
		static std::shared_ptr<CVkInstance> m_instance;
		static std::shared_ptr<CVkDevice>   m_device;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			m_instance = CreateInstance();
			Assert::IsNotNull(m_instance.get());

			m_device = CreateDevice(m_instance);
			Assert::IsNotNull(m_device.get());
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			VkResult result = m_device->WaitIdle();
			Assert::AreEqual(result, VK_SUCCESS);

			m_device.reset();
		}

		TEST_METHOD(Reset_Success)
		{
			VkCommandPoolCreateInfo info;
			memset(&info, 0, sizeof(info));
			info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

			std::shared_ptr<CVkCommandPool> commandPool;
			VkResult result = m_device->CreateCommandPool(info, NULL, commandPool);
			Assert::AreEqual(result, VK_SUCCESS);

			VkCommandPoolResetFlags flags = 0;
			result = commandPool->Reset(flags);
			Assert::AreEqual(result, VK_SUCCESS);
		}
	};

	std::shared_ptr<CVkDevice>   CVkCommandPoolTest::m_device;
	std::shared_ptr<CVkInstance> CVkCommandPoolTest::m_instance;

}