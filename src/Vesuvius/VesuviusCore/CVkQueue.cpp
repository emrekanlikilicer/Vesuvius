#include "CVkQueue.h"

using namespace vesuvius;

CVkQueue::CVkQueue(
	_In_ VkQueue    Queue,
	_In_ uint32_t   QueueFamilyIndex,
	_In_ uint32_t   QueueIndex
):m_queue(Queue),
  m_queueFamilyIndex(QueueFamilyIndex),
  m_queueIndex(QueueIndex)
{
}
