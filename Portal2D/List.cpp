#include "List.h"
#include "Definitions.h"

void list::addList(list::List<records::DataAboutTheChampion> **list, std::ifstream &fin)          // �������� � ������������� ������
{
	list::List<records::DataAboutTheChampion> *add = *list;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;

	while (!fin.eof())
	{
		int lengthLine = records::countLengthLine(finForSize);     // ������ ������ ������ ��� ���������� �������-������
		buf = new char[lengthLine];
		fin.getline(buf, lengthLine);
		add->next = new list::List<records::DataAboutTheChampion>;
		add->value = records::initializationDataAboutTheChampion(buf);
		add = add->next;
		add->next = NULL;
		delete[] buf;
	}
	finForSize.close();
}

void list::addInCertainPlace(list::List<records::DataAboutTheChampion> **begin, int placeNumber, records::DataAboutTheChampion newChampion)       // ������� �������� ������ � ����� ������������ �� ��������������� ����� 
{
	if (placeNumber == 0)
	{
		list::addBegin(begin, newChampion);           // ������� � ������ ������
	}
	else
	{
		list::List<records::DataAboutTheChampion> *insert = *begin;         // ����� ��������� �� ������ ������

		for (int i = 0; i < placeNumber - 1; i++)
		{
			insert = insert->next;      // ������������� �� ������� �����
		}
		list::List<records::DataAboutTheChampion> *end = insert->next;       // ��������� �� ������� �� ������� ����� ��������� ����� ������� ������ 
		list::List<records::DataAboutTheChampion> *add = new list::List<records::DataAboutTheChampion>;           // ����� �������
		insert->next = add;             // ��������� ����������� �������� �� ����� �������
		add->value = newChampion;       // ������������� ������ ��������
		add->next = end;                // ��������� ������ �������� � ���������� �������� ������
	}
}

void list::freeMemory(list::List<records::DataAboutTheChampion> *begin)       // ������������ ������ �� ������ 
{
	list::List<records::DataAboutTheChampion> *cleaner = begin;        // ����� ��������� �� ������ ������

	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}

void list::deleteCurrentElement(list::List<char> **types, char element)
{
	bool flag = true;
	list::List<char> *del = *types;
	list::List<char> *temp = *types;

	if ((*types)->value == element)
	{
		*types = (*types)->next;
		delete del;
	}
	else
	{
		temp = temp->next;
		while (flag)
		{
			if (temp->value == element)
			{
				del = temp;
				temp = temp->next;
				(*types)->next = temp;
				delete del;
				flag = false;
			}
		}
	}
}