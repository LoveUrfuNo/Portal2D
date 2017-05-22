#pragma once
#include "Tree.h"
#include "HighScores.h"
#include "List.h"
#include "Instruments.h"
#include "SortingMethods.h"
#include <conio.h>

namespace search
{
	void printFoundChampions(list::List<records::DataAboutTheChampion> *list, int key);

	int comparison(char *name, std::string str);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name);

	/* ��������� ������ ���������� ������������� � ���������� ��������� �� ���� ������ */
	template<typename T> list::List<records::DataAboutTheChampion> *searchAllElements(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree,
		T data,
		tree::BranchForNumber<records::DataAboutTheChampion>*(*searchFunc)(tree::BranchForNumber<records::DataAboutTheChampion> *, T)
	)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;       // ������ � ���������� ������������� 
		tree::BranchForNumber<records::DataAboutTheChampion> **search = &tree;      // �������� ��������� �� ��������� ��� ������
		tree::BranchForNumber<records::DataAboutTheChampion> *temp = *search;       // ���������, ��� ������������� ������

		while (temp)
		{
			if (counterOfLoop)     // �� ������ �������� 
			{
				*search = searchFunc(temp->right, data);    // �������� �������, ��������������� ��������� ���������� ������, 
														   //  �� ������ ����� �������� ��������� ��������� (����� �� ����� ��� ���������� �����������)
			}
			else     // ������ �������� 
			{
				*search = searchFunc(temp, data);       // �������� �������, ��������������� ��������� ���������� ������, �� ������ ������
			}
			temp = *search;      // �������������� ��������� 
			if (temp)
			{
				list::addBegin(&list, temp->data);      // ���� ���� ���, �� ��������� � ������ ���������� �����������
			}
			counterOfLoop++;     // ������� ��������++
		}

		return list;
	}

	records::DataAboutTheChampion searchBySubstringOfOneResult(records::DataAboutTheChampion subjectOfSearch, char *substring);

	list::List<records::DataAboutTheChampion> *searchBySubstringAllResults(list::List<records::DataAboutTheChampion> *result, char *substring);
}