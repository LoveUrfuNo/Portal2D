#pragma once

#include <iostream>

#include <windows.h>
#include <conio.h>
#include <stdio.h> 

#include "Instruments.h"
#include "HighScores.h"
#include "Gameplay.h"
#include "Definitions.h"
#include "Queue.h"
#include "List.h"
#include "Tree.h"
#include "Structures.h"

using namespace std;

/*������� ������� ����*/
struct BordersOfMenu
{
	int upBorder;																// ����� ������� ������� ����	
	int lowerBorder;															// ����� ������ ������� ����
};

namespace menu
{
	char* getFileNameFormNumberOfLevel(int numberOfLevel);

	// ������ �������
	void drawLogo();

	// ������������� ��������� ������������� ����� � ������� Start
	void doPointStart(queue::Queue<int> *queue, bool flag);

	// ������������� ��������� ������������� ����� � ������� Records
	void doPointRecords();

	// ������������� ��������� ������������� ����� � ������� Search, ������� Records
	void doPointRecordSearch();

	// ��������� ���������� ���� � ��� ����� �� �����
	int controlMenu(BordersOfMenu borders, string points[]);

	// ��������� ��������� ������
	void fillArray(string array[], int count, char divider);

	// ������������� ��������� ������������� ����� � ������� ����
	void doMainMenu(queue::Queue<int> *queue, bool flag);

	/*��������� �������*/
	void menu();

	// ������� ���� �� �����
	void printMenu(string str[], int points, int key);
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
	Start,
	Records,
	Exit,
};

enum PointStart
{
	Instruction,
	RandomLevel,
	Level1,
	Level2,
	Level3,
	Level4,
	Level5,
	BackLevel,
};

enum PointRecords
{
	Search,
	ShowAllRecords,
	BestOfTheBest,
	BackRecords
};

enum PointRecordsSearch
{
	ByScore,
	ByLevel,
	ByName,
	BySubstring,
	BackRecordsSearch
};


