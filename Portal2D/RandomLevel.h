#pragma once

#include "Queue.h"

namespace random
{
	/*   ���������� ������� ������� �������   */
	void inline initializeArrayWithDifferentNumbers(int *arr);

	/*   �������������� ������� �� ������� �� ���������� ������� � ���������� ������� �������   */
	template <typename T> T initializeQueueAndReturnHead(queue::Queue<T> *queue)
	{
		int *arr = new int[NUMBER_OF_LEVELS];
		if (!queue->head)
		{
			queue::initializeArrayWithDifferentNumbers(arr);
			queue::addQueue(queue, arr, NUMBER_OF_LEVELS);
		}
		else
		{
			std::cout << " ";
		}
		return queue::deQueue(queue);
	}
}