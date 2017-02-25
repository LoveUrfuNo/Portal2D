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
	
	//menu::functionCaller(menu::menu());

	game::Map** map = game::createMap(MAP_HEIGHT, MAP_WIDTH, "Lvl_1.txt");

	game::drawFrame(MAP_HEIGHT, MAP_WIDTH, map);


	while(true)
	{
		if(_kbhit())
		{
			switch (_getch())
			{
			case(A_LOWER_CASE /*|| A_UPPER_CASE*/):
				int x = NULL;
				int y = NULL;
				for(int i = 0; i < MAP_HEIGHT; i++)
				{
					for(int j = 0; j < MAP_WIDTH; j++)
					{
						if(map[i][j].type == HERO)
						{
							x = i;
							y = j;
						}
					}
				}
				if(map[y-1][x].block.passable == false)
				{
					map[y][x].type = EMPTY_SPACE;
					map[y - 1][x].type = HERO;
				}
			}
		}
		system("cls");
		game::drawFrame(MAP_HEIGHT, MAP_WIDTH, map);
	}


	system("pause");

	return 0;
}
