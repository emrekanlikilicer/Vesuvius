#include "stdafx.h"
#include "CppUnitTest.h"
#include "CVkInstance.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace vesuvius;

namespace vesuviusTest
{
	TEST_CLASS(CVkCommandBufferTest)
	{
	private:
		static std::shared_ptr<CVkInstance> m_instance;
		static std::shared_ptr<CVkDevice>   m_device;
		static std::shared_ptr<CVkCommandPool> m_commandPool;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			m_instance = CreateInstance();
			Assert::IsNotNull(m_instance.get());

			m_device = CreateDevice(m_instance);
			Assert::IsNotNull(m_device.get());

			VkCommandPoolCreateInfo info;
			memset(&info, 0, sizeof(info));
			info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;

			VkResult result = m_device->CreateCommandPool(info, NULL, m_commandPool);
			Assert::AreEqual(result, VK_SUCCESS);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			VkResult result = m_device->WaitIdle();
			Assert::AreEqual(result, VK_SUCCESS);

			m_device.reset();
		}

		TEST_METHOD(Reset_Success)
		{
			std::vector<std::shared_ptr<CVkCommandBuffer>> bufferVector;
			VkResult result = 
				m_commandPool->AllocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_PRIMARY,
														1, bufferVector);
			Assert::AreEqual(result, VK_SUCCESS);
			Assert::AreEqual((int)bufferVector.size(), 1);

			std::shared_ptr<CVkCommandBuffer> commandBuffer = bufferVector[0];

			Assert::IsNotNull(commandBuffer.get());

			result = commandBuffer->Reset(0);
			Assert::AreEqual(result, VK_SUCCESS);
		}

		TEST_METHOD(BeginEnd_Success)
		{
			std::vector<std::shared_ptr<CVkCommandBuffer>> bufferVector;
			VkResult result =
				m_commandPool->AllocateCommandBuffers(VK_COMMAND_BUFFER_LEVEL_PRIMARY,
					1, bufferVector);
			Assert::AreEqual(result, VK_SUCCESS);
			Assert::AreEqual((int)bufferVector.size(), 1);

			std::shared_ptr<CVkCommandBuffer> commandBuffer = bufferVector[0];

			Assert::IsNotNull(commandBuffer.get());

			result = commandBuffer->Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
			Assert::AreEqual(result, VK_SUCCESS);

			result = commandBuffer->End();
			Assert::AreEqual(result, VK_SUCCESS);
		}
	};

	std::shared_ptr<CVkDevice>   CVkCommandBufferTest::m_device;
	std::shared_ptr<CVkInstance> CVkCommandBufferTest::m_instance;
	std::shared_ptr<CVkCommandPool> CVkCommandBufferTest::m_commandPool;
}