#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

#include "Instruments.h"
#include "Records.h"
#include "Gameplay.h"
#include "Definitions.h"
#include "Queue.h"
#include "List.h"
#include "Tree.h"
#include "Structures.h"

using namespace std;

/*��������� ���� �� ������� ������� ��� �����*/
struct ParametersForMenu
{
	int upBorder;																// ����� ������� ������� ����	
	int lowerBorder;															// ����� ������ ������� ����
	void(*print)(int);															// ������� ���� �� �����
};

namespace menu
{
	//������ �������
	void drawLogo();

	//������� ������� �������� ����, �� ������� ����������� ������������
	void printMenu(int key);

	//������� ������� ����, �� ������� ����������� ������������ � ������ Start
	void printPointStart(int key);

	//������� ������� ����, �� ������� ����������� ������������ � ������ Records
	void printPointRecord(int key);

	void printPointSearch(int key);

	//������������� ��������� ������������� ����� � ������� Start
	void doPointStart(queue::Queue<int> *queue, bool flag);

	//������������� ��������� ������������� ����� � ������� Records
	void doPointRecords();

	void doPointRecordSearch();

	//��������� ���������� ���� � ��� ����� �� �����
	int controlMenu(ParametersForMenu borders);

	//������������� ��������� ������������� ����� � ������� ����
	void menu(queue::Queue<int> *queue, bool flag);
}

enum Colors
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkMagenta = 5,
	Brown = 6,
	LightGrey = 7,
	DarkGrey = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

enum MenuPoints
{
	Start = 1,
	Records,
	Exit,
};

enum PointStart
{
	Instruction = 1,
	RandomLevel,
	Level1,
	Level2,
	BackLevel,
};

enum PointRecords
{
	Search = 1,
	ShowAllRecords,
	Show10Records,
	BestOfTheBest,
	BackRecords
};

enum PointRecordsSearch
{
	ByScore = 1,
	ByLevel,
	ByName,
	BySubstring,
	BackRecordsSearch
};


