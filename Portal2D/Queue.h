#pragma once 
#include "Structures.h" 

namespace queue
{
	/** 
	 * ���������� ������� ������ �������.
	 */
	template <typename T> int checkCurrentSizeOfQueue(queue::Queue<T> queue)
	{
		int resultOfCount = 0;
		while (queue.head)
		{
			resultOfCount++;
			queue.head = queue.head->next;
		}

		return resultOfCount;
	}

	/**
	 * �������������� ������� �� ������� ������ dataArray.
	 */
	template <typename T> void addQueue(queue::Queue<T> *queue, T *dataArray, int numberOfElements)
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			enQueue(queue, dataArray[i]);
		}
	}

	/**
	 * ��������� ������� � �������.
	 */
	template <typename T> void enQueue(queue::Queue<T> *queue, T newData)
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

	/**
	 * ������� ������� �� ������� � ���������� ���. (� ������)
	 */
	template <typename T> T deQueue(queue::Queue<T> *queue)
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

	/**
	 * ����������� ������, ���������� ��� ������ �������.
	 */
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
}
