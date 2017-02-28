#include "List.h"

void list::addList(List **begin, std::ifstream &fin)          // �������� � ������������� ������
{
	List *add = *begin;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;
	while (!fin.eof())
	{
		int lengthLine = records::countLengthLine(finForSize);
		buf = new char[lengthLine];
		fin.getline(buf, lengthLine);
		add->next = new List;
		add->champion = records::sortingDataAboutTheChampion(buf);
		add = add->next;
		add->next = NULL;
	}
	finForSize.close();
	delete[] buf;
}

void list::addBegin(List **begin, records::DataAboutTheChampion newChampion)        // ������� � ������ ������
{
	List *add = new List;
	add->champion = newChampion;
	add->next = *begin;
	*begin = add;
}

void list::addInCertainPlace(List **begin, int placeNumber, records::DataAboutTheChampion newChampion)       // ������� �������� ������ � ����� ������������ �� ��������������� ����� 
{
	if (placeNumber == 0)
	{
		addBegin(begin, newChampion);           // ������ � ������ ������
	}
	else
	{
		List *insert = *begin;         // ����� ��������� �� ������ ������
		for (int i = 0; i < placeNumber - 1; i++)
		{
			insert = insert->next;      // ������������� �� ������� �����
		}
		List *end = insert->next;       // ��������� �� ������� �� ������� ����� ��������� ����� ������� ������ 
		List *add = new List;           // ����� �������
		insert->next = add;             // ��������� ����������� �������� �� ����� �������
		add->champion = newChampion;    // ������������� ������ ��������
		add->next = end;                // ��������� ������ �������� � ���������� �������� ������
	}
}

void list::freeMemory(List *begin)       // ������������ ������ �� ������ 
{
	List *cleaner = begin;        // ����� ��������� �� ������ ������
	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}