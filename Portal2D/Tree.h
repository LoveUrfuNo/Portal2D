#pragma once
#include "Structures.h"

enum Parametr
{
	SCORE = 1, LEVEL = 2, STRING = 3, SUBSTRING = 4
};

namespace tree
{
	/**
	 * ��������� ������� � ������.
	 */
	void addInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&tree, int variant);

	/**
	 * ���������� ����������� �������.
	 */
	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * ���������� ������������ �������.
	 */
	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * ����������� ������, ���������� ��� ������.
	 */
	void freeMemory(tree::BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * �������������� ������ � ����������� �� ��������� "varaint".
	 */
	void initializeTree(BranchForNumber<records::DataAboutTheChampion> **tree, char *fileName, int variant);
}