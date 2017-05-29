#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Structures.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	/**
	 * �������������� ���� � ������ ������ �����������.
	 */
	void overwriteFile(list::List<DataAboutTheChampion> *listWithAll);

	/**
	 * ���������� ����� ������ ����������� � ����������� �� ������ � �����,
	 * ����� �������� � ���� �� ������� �������.
	 */
	int getPlaceOfChampionInOrder(list::List<DataAboutTheChampion> *listWithAll, DataAboutTheChampion newChampion);

	/**
	 * �������: "add" - �������� � �������, "show" - �������� ��� ������� (�� ������ 10�).
	 */
	void addInRecordsOrShowRecords(DataAboutTheChampion *newChampion, char *variant);

	/**
	 * �������������� ���������� � ������� � ������������ �� ������ � ���������� ��.
	 */
	DataAboutTheChampion getChampionWithDataFromBuffer(char *buf);

	/**
	 * ������� �� ������ ������ ��������� �� ������.
	 */
	void printBestPlayerInLevel(int levelNumber);

	/**
	 * ������� ������� �������� � ������� != rightLevel �
	 * ���������� ������ ��������� ����� ������������ ������ rightLevel.
	 */
	DataAboutTheChampion getBestResultOnTheLevel(list::List<DataAboutTheChampion> *listWithAll, int rightLevel);

	/**
	 * ���������� ����� ������.
	 */
	int getLineLength(std::ifstream &finForSize);
}

namespace list 
{
	/**
	 * C������� � �������������� ������ �� �����.
	 */
	void addList(List<records::DataAboutTheChampion> **begin, std::ifstream &fin);   
}