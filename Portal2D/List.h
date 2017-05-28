#pragma once
#include <conio.h>
#include "HighScores.h"

namespace list
{
	/**
	 * ����������� ������, ���������� ��� ������� ������.
	 */
	void freeMemory(List<records::DataAboutTheChampion> *begin);

	/**
	 * ������� �������� � ������ ������.
	 */
	template<class T1, class T2> void addBegin(T1 **list, T2 insertable)
	{
		T1 *add = new T1;
		add->value = insertable;
		add->next = *list;
		*list = add;
	}

	/**
	 * ��������� ������ ����������� �� ������������ ����� � ������.
	 */
	void addInCertainPlace(List<records::DataAboutTheChampion> **list,
		int placeNumber,
		records::DataAboutTheChampion newChampion);

	/**
	 * ������� ������� �� ������.
	 */
	void deleteCurrentElement(list::List<char> **types, char element);
}
