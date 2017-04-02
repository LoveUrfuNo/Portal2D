#include "List.h"

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

template<class T1, class T2>
void list::addBegin(T1 **begin, T2 insertable)        // ������� � ������ ������
{
	T1 *add = new T1;
	add->value = insertable;
	add->next = *begin;
	*begin = add;
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

template <class T1, class T2>
void list::deleteCurrentElement(list::List<T1> *types, T2 element)
{
	T1 *del = types;
	T1 *delNext = del->next;

	while (delNext->next != EMPTY_SPACE)
	{
		if (delNext == element)
		{
			del->next = delNext->next;
		}

		del = delNext;
		delNext = delNext->next;
	}
}

template <typename T>
T list::peek(List<T>* types)
{

	T top = types->element;
	return top;
}
