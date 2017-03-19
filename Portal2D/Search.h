#pragma once
#include "Tree.h"
#include "Records.h"
#include "List.h"
#include "Instruments.h"
#include <conio.h>

namespace search
{
	/* � ����������� �� ��������� ���������� ��������� ��������� ������ */
	template<typename T> void setSearchParametr(int parametr)
	{
		list::List<records::DataAboutTheChampion> *list = NULL;       // ������ � ���������� ������������� 
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;        // ������ �� ����� ������������� 
		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		char *name = new char[1000];
		switch (parametr)
		{
		case SCORE:
			createTree(&tree, FILE_NAME_RECORDS, SCORE);     // ������� � �������������� ������ �� �����
			std::cout << "\tenter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = searchAllElements<double>(tree, numberOfScore, searchByScoreOfOneResult);       // ��������� �� ������ � ���������� ������������� 
			break;

		case LEVEL:
			createTree(&tree, FILE_NAME_RECORDS, LEVEL);     // ������� � �������������� ������ �� �������
			std::cout << "\tenter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = searchAllElements<int>(tree, numberOfLevel, searchByLevelOfOneResult);       // ��������� �� ������ � ���������� ������������� 
			break;

		case STRING:
			createTree(&tree, FILE_NAME_RECORDS, STRING);     // ������� � �������������� ������ �� ������
			std::cout << "\tenter the string: ";
			std::cin >> name;
			std::cout << "\n";
			list = searchAllElements<char*>(tree, name, searchByStringOfOneResult);       // ��������� �� ������ � ���������� ������������� 
			break;
		}
		printFoundChampions(list);        // �������� ������ � ���������� �������������
		list::freeMemory(list);
		tree::freeMemory(tree);
		delete[] name;
		_getch();
		system("cls");
	}

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list);

	int comparison(char *name, std::string str);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name);

	/* ��������� ������ ���������� ������������� � ���������� ��������� �� ���� ������*/
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
				                                      // �� ������ ����� �������� ��������� ��������� (����� �� ����� ��� ���������� �����������)
			}
			else    // ������ �������� 
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
}