#include "List.h"
#include "SortingMethods.h"


void records::addInRecordsOrShowRecords(
	records::DataAboutTheChampion *newChampion, char *variant)
{
	int counterOfPrintedChampions = 0;
	list::List<records::DataAboutTheChampion> *begin
		= new list::List<records::DataAboutTheChampion>; // ��������� �� ������ ������
	std::ifstream fin(FILE_NAME_RECORDS);

	list::addList(&begin, fin);       // �������������� ������

	if (!strcmp(variant, "show"))     // �������� ��� �������
	{
		std::cout << "\n\t\t\t\t\t\tALL RECORDS" << std::endl;
		std::cout << "\n";

		while (begin->next && counterOfPrintedChampions < 10000)
		{
			counterOfPrintedChampions++;
			std::cout << "\n\t\t\t  " << counterOfPrintedChampions
				<< ". name: " << begin->value.name
				<< " level: " << begin->value.level
				<< " score: " << begin->value.score << std::endl;

			begin = begin->next;
		}

		std::cout << "\n";
		system("pause");
		system("cls");
	}
	else if (!strcmp(variant, "add"))     // �������� � �������
	{
		int placeInRank = records::getPlaceOfChampionInOrder(begin, *newChampion);    // ������ ������������� ����� � ������
		list::addInCertainPlace(&begin, placeInRank, *newChampion);          // ��������� � ��������� �����
		records::overwriteFile(begin);               // ���������� ����� 
	}

	fin.close();
	list::freeMemory(begin);
}

void records::printBestPlayerInLevel(int levelNumber)
{
	list::List<records::DataAboutTheChampion> *begin
		= new list::List<records::DataAboutTheChampion>;  // ��������� �� ������ ������
	std::ifstream fin(FILE_NAME_RECORDS);

	begin->next = NULL;
	list::addList(&begin, fin);    // �������������� ������

	records::DataAboutTheChampion bestResult = records::getBestResultOnTheLevel(begin, levelNumber);
	if (bestResult.name == "_errorEmptyListOfRecords")      // ���� ������ �� ����� �� ������ ������
	{
		std::cout << " -> Be the first at this level! " << std::endl;
	}
	else
	{
		std::cout << " -> name: " << bestResult.name
			<< " score: " << bestResult.score << std::endl;
	}

	fin.close();
}

records::DataAboutTheChampion records::getBestResultOnTheLevel(
	list::List<records::DataAboutTheChampion> *begin, int rightLevel)
{
	bool counterChampionsInRightLevel = false;

	list::List<records::DataAboutTheChampion> *cleaner = begin;    // ����� ��������� �� ������ ������
	list::List<records::DataAboutTheChampion> *end = NULL;         // ��������� ��� �������� ����� ������

	records::DataAboutTheChampion bestResult;
	bestResult.score = NULL;
	while (begin && bestResult.score == NULL)
	{
		if (begin->value.level != rightLevel && bestResult.score == NULL)
		{
			if (end)
				end->next = NULL;

			cleaner = begin;
			begin = begin->next;
			delete cleaner;
		}
		else
		{
			end = begin;
			counterChampionsInRightLevel++;
			bestResult = begin->value;
			begin = begin->next;
		}
	}

	if (!counterChampionsInRightLevel)       // ���� ������ � �������� � ������� rightLevel ���, �� ���������� ���-������
	{
		bestResult.name = "_errorEmptyListOfRecords";
	}

	list::freeMemory(begin);

	return bestResult;
}

int records::getLineLength(std::ifstream &finForSize)
{
	int lineLength = 0;
	char temp = ' ';
	while (temp != '>')
	{
		finForSize >> temp;
		lineLength++;
	}

	return ++lineLength;
}

void records::overwriteFile(list::List<records::DataAboutTheChampion> *begin)        // ���������� �����
{
	std::ofstream fout(FILE_NAME_RECORDS);
	while (begin->next != NULL)
	{
		fout << begin->value.name << "|"
			<< begin->value.score << "|"
			<< begin->value.level << ">";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}

		begin = begin->next;
	}

	fout.close();
}

int records::getPlaceOfChampionInOrder(list::List<records::DataAboutTheChampion> *begin,
	records::DataAboutTheChampion newChampion)
{                                                                 
	int placeInOrder = 0;
	list::List<records::DataAboutTheChampion> *list = begin;
	while (list->value.level > newChampion.level)    // ���� ������� ����������� �� ������ ������ ��� � ������������ �����������
	{
		list = list->next;
		placeInOrder++;
	}
	while (list->value.score > newChampion.score && list->value.level == newChampion.level)   // ���� ���-�� ����� �� ������ ������ ������������ � ������� �� ������ ����� ������ ������������ �����������
	{
		list = list->next;
		placeInOrder++;
	}

	return placeInOrder;
}

records::DataAboutTheChampion records::getChampionWithDataFromBuffer(char *buf)
{
	char points[25], lvl[2];
	records::DataAboutTheChampion champion = {};

	int counterLetter = 0, i = 0;
	while (buf[counterLetter] != '|')        // ������������� ���� name �� ������ �� ���� �������
	{
		champion.name += buf[counterLetter];
		counterLetter++;
	}

	counterLetter++;
	while (buf[counterLetter] != '|')        // ������������� ���� score 
	{
		points[i] = buf[counterLetter];
		i++;
		counterLetter++;
	}

	double score = atof(points);
	champion.score = score;
	counterLetter++;
	i = 0;
	while (buf[counterLetter] != '>')        // ������������� ���� level 
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}

	int level = atoi(lvl);
	champion.level = level;

	return champion;
}

void list::addList(list::List<records::DataAboutTheChampion> **list, std::ifstream &fin)          // �������� � ������������� ������
{
	list::List<records::DataAboutTheChampion> *add = *list;
	std::ifstream finForSize(FILE_NAME_RECORDS);
	char *buf = NULL;

	while (!fin.eof())
	{
		int lengthLine = records::getLineLength(finForSize);     // ������ ������ ������ ��� ���������� �������-������
		buf = new char[lengthLine];
		fin.getline(buf, lengthLine);

		add->next = new list::List<records::DataAboutTheChampion>;
		add->value = records::getChampionWithDataFromBuffer(buf);
		add = add->next;
		add->next = NULL;

		delete[] buf;
	}

	finForSize.close();
}