#include "Gameplay.h"
#include "Map.h"

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

			switch (currentSymbol)			// 
			{
			case HERO_SYMBOL:					// ���� ������� ������ ����� "H", ��
				map[i][j].type = HERO;			// ��� ������� ������ ���������� "�����"
				gameInfo->hero.xCoordinate = j;	// ������������ ��� ����������
				gameInfo->hero.yCoordinate = i;
				map[i][j].passable = true;
				break;

			case BLOCK_SHARP:				// ���� ������� ������ ����� "�������", ��
				map[i][j].type = BLOCK;		// ��� ������� ������ ���������� "����"
				map[i][j].passable = false;	//������ ���������� ������������
				break;

			case EMPTY_SPACE:				// ���� ������� ������ ����� "_", ��
				map[i][j].type = EMPTY_SPACE;	// ��� ������� ������ ���������� "������ ������������"
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case AIM_DOT:					// ���� ������� ������ ����� "�����", ��
				map[i][j].type = AIM_DOT;	// ��� ������� ������ ���������� "������"
				gameInfo->aim.xCoordinate = j;	// ������������ ��� ����������
				gameInfo->aim.yCoordinate = i;
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case BLACK_WALL_S:				// ���� ������� ������ ����� "X", ��
				map[i][j].type = BLACK_WALL;	// ��� ������� ������ ���������� "������������ �����"
				gameInfo->blackWall.xCoordinate = j;
				gameInfo->blackWall.yCoordinate = i;
				map[i][j].passable = false;	// ������ ���������� ������������
				break;

			case EXIT_S:					// ���� ������� ������ ����� "X", ��
				map[i][j].type = EXIT;		// ��� ������� ������ ���������� "�����"
				gameInfo->exitFromLevel.xCoordinate = j;
				gameInfo->exitFromLevel.yCoordinate = i;
				map[i][j].passable = true;	// ������ ���������� ����������
				break;

			case RED_PORTAL:				  // ���� ������� ������ ����� "O", ��
				map[i][j].type = RED_PORTAL;  // ��� ������� ������ ���������� "������� ������"
				gameInfo->redPortal.xCoordinate = j;
				gameInfo->redPortal.yCoordinate = i;   // ������������ ��� ����������
				map[i][j].passable = true;    // ������ ���������� ����������
				break;

			case BLUE_PORTAL:
				map[i][j].type = BLUE_PORTAL;   // ���� ������� ������ ����� "O", ��
				gameInfo->bluePortal.xCoordinate = j;    // ��� ������� ������ ���������� "������� ������"
				gameInfo->bluePortal.yCoordinate = i;	// ������������ ��� ����������
				map[i][j].passable = true;      // ������ ���������� ����������
				break;

			case BUTTON_S:
				map[i][j].type = BUTTON;
				gameInfo->button.xCoordinate = j;
				gameInfo->button.yCoordinate = i;
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
