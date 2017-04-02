#include "List.h"
#include "Definitions.h"

void list::addList(list::List<records::DataAboutTheChampion> **begin, std::ifstream &fin)          // �������� � ������������� ������
{
	list::List<records::DataAboutTheChampion> *add = *begin;
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
	list::List<char> *begin = *types;

	while ((*types)->value != EMPTY_SPACE && flag && del)
	{
		if ((*types)->value == element)
		{
			begin = begin->next;
			del = (*types);
			delete del;
			flag = false;
		}
		else
		{
			*types = (*types)->next;
		}
	}
	*types = begin;
}