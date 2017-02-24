#include <iostream>
#include "Menu.h"
#include "Gameplay.h"

using namespace std;

/*
	��������! (��� �� ����� ��������� ������� - ���� ��� � ���� ������)

	1)	�����, �������������� ����, ������ ���� ����������� �������� � ��������� ��������, ������� � ��������.
	Line, SavingsAccount

	2)	����� ���������� ������ ���� �������� � ��������� ��������, ������� � �������.
	line, savingsAccount

	3)	����������� ��������� (������� �������� ������������) ������ ���� �������� � ������� �������� � ������ �������������� � �������� �����������.
	MAX_ITERATIONS, COLOR_RED, PI

	4)	�������� ������� � ������� ������ ���� ���������, ���� ����������� � ��������� �������� � ���������� � �������.
	getName(), computeTotalWidth()

	5)	�������� ����������� ��� ������� ���������� � ������ ��������.
	model::analyzer, io::iomanager, common::math::geometry            !!!!!!!!!!!(��� ��������� ������ ������ ��� ���� ��������� ������� ���������� � ������������ ��� (namespace) � ������)

	6)	������� �������� ����� ����� � �������� ����� ��������� ������.
	template<class T> 

	7)	������������ � ���������� � ������ ������ ������������ � ������ ��������.
	exportHtmlSource(); // ������: exportHTMLSource();

	8)	������������� (� ����� ������ - �����������) ���������� ������� ������ �� �� ���, ��� � � �� ����.
	void setTopic(Topic* topic)      // ������: void setTopic(Topic* value)
		                             // ������: void setTopic(Topic* aTopic)
			                         // ������: void setTopic(Topic* t)
	9)	��� ����� ������� ���������� ��-���������.
	fileName;   // �� �������������: imyaFayla

	10)	����������, ������� ������� ������� ���������, ������� �������� �������� �������, ������� ��������� ������� ��������� � ���������.

	11)	����� �������� �� ����������� ����, ������� �������� �������� �������� �������� � ������ �������.  (�������� ��������� �� �����������)
	line.getLength();   // �� �������������: line.getLineLength();

	12)	����� find ����� ���� ������������ � ��������, �������������� �����-���� �����.
	findMinElement();

	13)	������� n ������� ������������ ��� ������������� ����� ��������.
	nPoints, nLines

	14) ������� No ������� ������������ ��� ����������� ������ ��������.
	tableNo, employeeNo

	15)	������� �������� ���������� � ������.
	computeAverage();   // ������: compAvg();

	16)	������� �������� ��������������� ���������� ����������.
	Line* line; // �� �������������: Line* pLine;
		        // �� �������������: Line* linePtr;

	17)  ������ ������ ������� (����������) ���������� �����, ���������� ���������.
	bool isError; // ������: isNoError
	bool isFound; // ������: isNotFound

	18)	��������� � ������������� ����� ����� (����� �� �����) ������� � ����� ��� ����.
	enum Color {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE
	};
*/

int main()
{
	const int sizeOfMapHeight = 20;
	const int sizeOfMapWidth = 35;
	//menu::functionCaller(menu::menu());


	game::Map** map = game::createMap(sizeOfMapHeight, sizeOfMapWidth);

	//------------------------READING FILE---------------------------//
	char symbolMass[sizeOfMapHeight][sizeOfMapWidth];

	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			symbolMass[i][j] = BLOCK;
		}

		for (int j = sizeOfMapWidth - 1; j < sizeOfMapWidth; j++)
		{
			symbolMass[i][j] = BLOCK;
		}

	}

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			symbolMass[i][j] = BLOCK;
		}
	}

	for (int i = sizeOfMapHeight - 1; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			symbolMass[i][j] = BLOCK;
		}
	}

	//---------------------------------------------------//


	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			switch (symbolMass[i][j])
			{
			case BLOCK:
				map[i][j].type = BLOCK;
				map[i][j].block.xCoordinate = i;
				map[i][j].block.yCoordinate = j;
				break;
			default:
				map[i][j].type = EMPTY_SPACE;
				map[i][j].emptySpace.xCoordinate = i;
				map[i][j].emptySpace.yCoordinate = j;
				break;
			}
		}
	}

	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			switch (map[i][j].type)
			{
			case BLOCK:
				cout << BLOCK;
				break;
			case EMPTY_SPACE:
				cout <<EMPTY_SPACE;
				break;
			}
		}
		cout << endl;
	}

	system("pause");

	return 0;
}
