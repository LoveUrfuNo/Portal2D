#include "Search.h"
#include "Menu.h"

namespace search
{
	void printFoundChampion(list::List<records::DataAboutTheChampion> *list, int key)
	{
		list::List<records::DataAboutTheChampion> *check;

		if (key == BySubstring)
		{
			check = list->next;
		}
		else
		{
			check = list;
		}

		if (!check)
		{
			std::cout << "\t\t\t\t\tNoone here, be the first!" << std::endl;
		}
		else
		{
			while (check)
			{
				std::cout << "\t\t\t\tname: " << list->value.name
					<< " level: " << list->value.level
					<< " score: " << list->value.score
					<< std::endl;

				list = list->next;
				check = check->next;
			}
		}
	}

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score)
	{
		if (!tree || score == tree->data.score)     // ���� ����� ������ ��� ������� ���-�� �����
		{
			return tree;
		}

		if (score < tree->data.score)         // ���� �������� ������ ��� ���-�� ����� �������� �����������, �� ����� �� ������, ����� ������
		{
			search::searchByScoreOfOneResult(tree->left, score);
		}
		else
		{
			search::searchByScoreOfOneResult(tree->right, score);
		}
	}

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level)
	{
		if (!tree || level == tree->data.level)     // ���� ����� ������ ��� ������� ���-�� �����
		{
			return tree;
		}

		if (level < tree->data.level)         // ���� �������� ������ ��� ������� �������� �����������, �� ����� �� ������, ����� ������
		{
			search::searchByLevelOfOneResult(tree->left, level);
		}
		else
		{
			search::searchByLevelOfOneResult(tree->right, level);
		}
	}

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByNameOfOneResult(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name)
	{
		if (!tree || comparison(name, tree->data.name) == 0)     // ���� ����� ������ ��� ������� ���-�� �����
		{
			return tree;
		}

		if (comparison(name, tree->data.name) < 0)         // ���� �������� ������ ��� ��� �������� �����������, �� ����� �� ������, ����� ������
		{
			search::searchByNameOfOneResult(tree->left, name);
		}
		else
		{
			search::searchByNameOfOneResult(tree->right, name);
		}
	}

	int comparison(char *name, std::string str)
	{
		char *checking = new char[str.length() + 1];
		strcpy_s(checking, str.length() + 1, str.c_str());

		return _stricmp(name, checking);
	}

	records::DataAboutTheChampion searchBySubstringOfOneResult(
		records::DataAboutTheChampion subjectOfSearch, char *substring)
	{
		bool isResultPositive = false;
		int lengthOfSubstring = 0;
		char *stringForSearch = new char[subjectOfSearch.name.length() + 1];

		records::DataAboutTheChampion result = subjectOfSearch;
		strcpy_s(stringForSearch, subjectOfSearch.name.length() + 1, subjectOfSearch.name.c_str());

		for (lengthOfSubstring = 0; substring[lengthOfSubstring]; lengthOfSubstring++);      // ���������� ������� ���������

		if (subjectOfSearch.name.length() < lengthOfSubstring)
		{
			result.level = -1;      // ��������� ������ �������������
		}
		else
		{
			for (int i = 0, j = 0; i <= subjectOfSearch.name.length() && j <= lengthOfSubstring && !isResultPositive; i++, j++)
			{
				if (j == lengthOfSubstring)
					isResultPositive = true;         // ��������� ������ �������������

				if (!(stringForSearch[i] == substring[j]))
					j = -1;
			}
		}

		if (!isResultPositive)
			result.level = -1;

		delete[] stringForSearch;

		return result;
	}

	list::List<records::DataAboutTheChampion> *searchBySubstringAllResults(char *substring)
	{
		list::List<records::DataAboutTheChampion>
			*result,
			*listWithAll = new list::List<records::DataAboutTheChampion>,
			*begin = NULL;
		std::ifstream fin(FILE_NAME_RECORDS);
		records::DataAboutTheChampion temp;

		list::addList(&listWithAll, fin);
		result = new list::List<records::DataAboutTheChampion>;
		begin = result;
		begin->next = NULL;

		while (listWithAll)
		{
			temp = searchBySubstringOfOneResult(listWithAll->value, substring);
			if (temp.level != -1)       // temp.level == -1 ���� � ���������� ������ ����� ��������� ��������� � ������ ����� 0
			{
				result->next = new list::List<records::DataAboutTheChampion>;
				result->value = temp;
				result = result->next;
				result->next = NULL;
			}

			listWithAll = listWithAll->next;
		}

		fin.close();
		result = begin;
		list::freeMemory(listWithAll);

		return result;
	}
}
