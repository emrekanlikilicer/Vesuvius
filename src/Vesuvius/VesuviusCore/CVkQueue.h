#pragma once

#include "Vulkan.h"
#include <vector>

namespace vesuvius
{
	class CVkQueue
	{
	public:

	private:
		friend class CVkDevice;

	private:

		CVkQueue(
			_In_ VkQueue    Queue,
			_In_ uint32_t   QueueFamilyIndex,
			_In_ uint32_t   QueueIndex
		);

		uint32_t m_queueFamilyIndex;
		uint32_t m_queueIndex;

		VkQueue m_queue;
	};
}