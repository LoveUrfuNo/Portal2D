#include "Gameplay.h"
#include "Map.h"
#include "Definitions.h"
#include "Instruments.h"
#include "List.h"

// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
game::MapCell** game::createMap(char* levelName, GameInfo* gameInfo)
{
	game::MapCell** map = new game::MapCell*[MAP_HEIGHT];	//�������� ������������� �������
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		map[i] = new game::MapCell[MAP_WIDTH];
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

			switch (currentSymbol)			 
			{
			case HERO_SYMBOL:					// ���� ������� ������ ����� "H", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, HERO);
				gameInfo->hero.xCoordinate = j;	// ������������ ��� ����������
				gameInfo->hero.yCoordinate = i;
				break;

			case BLOCK_SHARP:				// ���� ������� ������ ����� "�������", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BLOCK);
				map[i][j].passable = false;	//������ ���������� ������������
				break;

			case EMPTY_SPACE:				// ���� ������� ������ ����� "_", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				break;

			case AIM_DOT:					// ���� ������� ������ ����� "�����", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, AIM_DOT);
				gameInfo->aim.xCoordinate = j;	// ������������ ��� ����������
				gameInfo->aim.yCoordinate = i;
				break;

			case BLACK_WALL_S:				// ���� ������� ������ ����� "X", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, BLACK_WALL);
				gameInfo->blackWall.xCoordinate = j;
				gameInfo->blackWall.yCoordinate = i;
				map[i][j].passable = false;	// ������ ���������� ������������
				break;

			case EXIT_S:					// ���� ������� ������ ����� "X", ��
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, EXIT);
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				break;

			case BUTTON_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, BUTTON);
				gameInfo->button.xCoordinate = j;
				gameInfo->button.yCoordinate = i;
				break;

			case TURRET_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, TURRET);
				gameInfo->turret.xCoordinate = j;
				gameInfo->turret.yCoordinate = i;
				break;

			case TURRET_EASY_S:
				map[i][j].types = new list::List<char>;
				list::addBegin(&map[i][j].types, EMPTY_SPACE);
				list::addBegin(&map[i][j].types, TURRET_EASY);
				gameInfo->turret_patrol.xCoordinate = j;
				gameInfo->turret_patrol.yCoordinate = i;
				break;

			default:
				break;
			}
		}
	}

	fin.close();

	return map;
}
