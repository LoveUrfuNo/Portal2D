#pragma once 

#include "Structures.h" 

#define NUMBER_OF_LEVELS 10 

namespace queue
{
	/**
	  ���������� ������� ������� �������
	  */
	void inline initializeArrayWithDifferentNumbers(int *arr)
	{
		for (int i = 0; i < NUMBER_OF_LEVELS; i++)
		{
			bool flag = true;
			int temp = rand() % NUMBER_OF_LEVELS + 1;
			for (int j = 0; j < NUMBER_OF_LEVELS; j++)
			{
				if (temp == arr[j])
				{
					i--;
					flag = false;
				}
			}
			if (flag)
			{
				arr[i] = temp;
			}
		}
	}

	template <typename T> int checkCurrentSizeOfQueue(queue::Queue<T> *queue)
	{
		int resultOfCount = 0;
		queue::Queue<T> *counter = queue;
		while (counter->head)
		{
			resultOfCount++;
			counter->head = counter->head->next;
		}
		return resultOfCount;
	}

	/**
	  *�������������� ������� �� ������� �� ���������� ������� � ���������� ������� �������
	  */
	template <typename T> T generatingRandomLevelNumber(queue::Queue<T> *queue)   
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
		return queue::pullElement(queue);
	}

	template <typename T> void pushInQueue(queue::Queue<T> *queue, T newData)
	{
		queue::Node<T> *node = new queue::Node<T>;
		node->data = newData;
		node->next = NULL;

		if (queue->head != NULL)
		{
			node->previous = queue->tail;   // "������" ��������� ���� �� ����� �������
			queue->tail->next = node;        
			queue->tail = node;             // ����� ������������ ����
		}
		else   // ���� ������� ������, �� �������������� 
		{
			node->previous = NULL;
			queue->tail = queue->head = node;
		}
	}

	template <typename T> void freeMemory(queue::Queue<T> *queue)
	{
		queue::Node<T> *cleaner;
		while (queue->head)            // ���� ���� ������ ������� �������� � ������
		{
			cleaner = queue->tail;
			queue->tail = queue->tail->previous;
			if (queue->head->next)
			{
				queue->tail->next = NULL;
			}
			else
			{
				queue->head = NULL;
			}
			delete cleaner;
		}
	}

	template <typename T> void addQueue(queue::Queue<T> *queue, T *dataArray, int numberOfElements)
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			pushInQueue(queue, dataArray[i]);
		}
	}

	template <typename T> T pullElement(queue::Queue<T> *queue)
	{
		T result = NULL;
		queue::Node<T> *clean = queue->head;
		if (queue->head)
		{
			result = queue->head->data;    // ��������� ������������ ������ �������
		}
		clean = queue->head;              
		queue->head = queue->head->next;
		delete clean;        // ������� ������

		return result;       // ���������� �������� ��������� ������
	}
}
