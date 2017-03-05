#include "Gameplay.h"
#include "Map.h"

<<<<<<< HEAD
// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
game::MapShell** game::createMap(char* levelName, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal)
=======
// ������� ����������� ����� �� ����� � ��������� ������ ��������, ��������� � �������� ��������� ��� ������
game::Map** game::createMap(char* levelName)
>>>>>>> Andrey
{
	game::MapShell** map = new game::MapShell*[MAP_HEIGHT];	//�������� ������������� �������
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		map[i] = new game::MapShell[MAP_WIDTH];
	}

	char currentSymbol;	// ���������� ��� ���������� �������� �������� �������, ���������� �� �����
	std::ifstream fin(levelName, std::ios_base::in);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			currentSymbol = fin.get();
			if (currentSymbol == NEW_LINE)	// ���� ������ ����� '\n', �� ���������� ���������� ���������� �������
				currentSymbol = fin.get();

			switch (currentSymbol)			// 
			{
			case HERO_SYMBOL:				// ���� ������� ������ ����� "H", ��
				map[i][j].type = HERO;		// ��� ������� ������ ���������� "�����"
				hero->xCoordinate = j;	// ������������ ��� ����������
				hero->yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLOCK_SHARP:				// ���� ������� ������ ����� "�������", ��
				map[i][j].type = BLOCK;		// ��� ������� ������ ���������� "����"
				map[i][j].xCoordinate = j;	// ������������ ��� ����������
				map[i][j].yCoordinate = i;
				map[i][j].passable = false;	//������ ���������� ������������
				break;

			case EMPTY_SPACE:				// ���� ������� ������ ����� "_", ��
				map[i][j].type = EMPTY_SPACE;	// ��� ������� ������ ���������� "������ ������������"
				map[i][j].xCoordinate = j;		// ������������ � ����������
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case AIM_DOT:					// ���� ������� ������ ����� "�����", ��
				map[i][j].type = AIM_DOT;	// ��� ������� ������ ���������� "������"
				aim->xCoordinate = j;	// ������������ ��� ����������
				aim->yCoordinate = i;
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case BLACK_WALL_S:				// ���� ������� ������ ����� "X", ��
				map[i][j].type = BLACK_WALL;	// ��� ������� ������ ���������� "������������ �����"
				map[i][j].xCoordinate = j;	// ������������ ��� ����������
				map[i][j].yCoordinate = i;
				map[i][j].passable = false;	// ������ ���������� ������������
				break;

			case EXIT_S:					// ���� ������� ������ ����� "X", ��
				map[i][j].type = EXIT;		// ��� ������� ������ ���������� "�����"
				map[i][j].xCoordinate = j;	// ������������ ��� ����������
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case RED_PORTAL:
				map[i][j].type = RED_PORTAL;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLUE_PORTAL:
				map[i][j].type = BLUE_PORTAL;
				map[i][j].xCoordinate = j;
				map[i][j].yCoordinate = i;
				map[i][j].passable = true;
				break;

			default:
				break;
			}
		}
	}
	fin.close();

	return map;
}
