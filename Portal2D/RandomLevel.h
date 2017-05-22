#pragma once
#include "RandomLevel.h"
#include "Queue.h"

namespace random
{
	/*   ���������� ������� ������� �������   */
	void initializesArrayWithUnmatchedNumbers(int *arr);

	/*   �������������� ������� �� ������� �� ���������� ������� � ���������� ������� �������   */
	template <typename T> T initializeQueueAndReturnHead(queue::Queue<T> *queue)
	{
		int *arr = new int[NUMBER_OF_LEVELS];
		if (!queue->head)
		{
			random::initializesArrayWithUnmatchedNumbers(arr);
			queue::addQueue(queue, arr, NUMBER_OF_LEVELS);
		}
		else
		{
			std::cout << " ";
		}

		return queue::deQueue(queue);
	}
}