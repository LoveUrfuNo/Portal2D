#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::MapShell** map)
{
	bool gameIsRunning = true; // ��������

	while (gameIsRunning)
	{
		int heroXCoordinate = findSomeTypeXCoordinate(HERO, map); //���� ���������� ����� �� ��� X
		int heroYCoordinate = findSomeTypeYCoordinate(HERO, map); //���� ���������� ����� �� ��� Y

		int PortalXCoordinate = findSomeTypeXCoordinate(RED_PORTAL, map);
		int PortalYCoordinate = findSomeTypeYCoordinate(RED_PORTAL, map);

		int aimXCoordinate = findSomeTypeXCoordinate(AIM_DOT, map); //���� ���������� ������� �� ��� X
		int aimYCoordinate = findSomeTypeYCoordinate(AIM_DOT, map); //���� ���������� ������� �� ��� X

		if (_kbhit()) // ���� ������ �������
		{
			switch (_getch()) // ������ �������
			{
			case A_LOWER_CASE:
				moveLeft(HERO, heroYCoordinate, heroXCoordinate, map);
				break;

			case D_LOWER_CASE:
				moveRight(HERO, heroYCoordinate, heroXCoordinate, map);
				break;

			case LEFT_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aimYCoordinate][aimXCoordinate - 1].type != RED_PORTAL) && (map[aimYCoordinate][aimXCoordinate - 1].type != BLUE_PORTAL))
					moveLeft(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				break;

			case RIGHT_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aimYCoordinate][aimXCoordinate + 1].type != RED_PORTAL) && (map[aimYCoordinate][aimXCoordinate + 1].type != BLUE_PORTAL))
					moveRight(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				break;

			case UP_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aimYCoordinate - 1][aimXCoordinate].type != RED_PORTAL) && (map[aimYCoordinate - 1][aimXCoordinate].type != BLUE_PORTAL))
					moveUp(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				break;

			case DOWN_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
					if ((map[aimYCoordinate + 1][aimXCoordinate].type != RED_PORTAL) && (map[aimYCoordinate + 1][aimXCoordinate].type != BLUE_PORTAL))
				moveDown(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				break;

			case SPACE_JUMP:
				jump(heroYCoordinate, heroXCoordinate, map); // ������
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, PortalYCoordinate, PortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, PortalYCoordinate, PortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
				break;

			/*case ENTER:
				
				break;*/

			default:
				break;
			}
		}
		game::clearScreen(); // ������� �����
		game::drawFrame(map);
		game::gravity(map); // ��������� ����������
		Sleep(75);
		game::clearScreen(); // ������� �����
	}
}

void game::jump(int heroYCoordinate, int heroXCoordinate, game::MapShell** map)
{
	if ((map[heroYCoordinate - 1][heroXCoordinate].passable == true) && // ���� ��� ������ ��� ������ ��������
		(map[heroYCoordinate - 2][heroXCoordinate].passable == true))
	{
		map[heroYCoordinate][heroXCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ����� ������� ������, � ������
		map[heroYCoordinate - 1][heroXCoordinate].type = HERO;	  // ���� ������� ������ �����, � ��� �� ��������� ���� � HP
		map[heroYCoordinate - 1][heroXCoordinate].healthPoints =
			map[heroYCoordinate][heroXCoordinate].healthPoints;

		game::drawFrame(map);

		map[heroYCoordinate - 1][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 2][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 2][heroXCoordinate].healthPoints =
			map[heroYCoordinate - 1][heroXCoordinate].healthPoints;

	}

	else if ((map[heroYCoordinate - 1][heroXCoordinate].passable == true) && // ���� �������� ������ ����
		(map[heroYCoordinate - 2][heroXCoordinate].passable == false))
	{
		map[heroYCoordinate][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 1][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 1][heroXCoordinate].healthPoints =
			map[heroYCoordinate][heroXCoordinate].healthPoints;
	}
}

void game::moveLeft(char type, int yCoordinate, int xCoordinate, game::MapShell** map)
{
	if (map[yCoordinate][xCoordinate - 1].passable == true) // ���� ������ ����� ��������� 
	{
		map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[yCoordinate][xCoordinate - 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
		map[yCoordinate][xCoordinate - 1].healthPoints =
			map[yCoordinate][xCoordinate].healthPoints;
	}
}

void game::moveRight(char type, int yCoordinate, int xCoordinate, game::MapShell** map)
{
	if (map[yCoordinate][xCoordinate + 1].passable == true) // ���� ������ ������ ���������
	{
		map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[yCoordinate][xCoordinate + 1].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		map[yCoordinate][xCoordinate + 1].healthPoints =
			map[yCoordinate][xCoordinate].healthPoints;
	}
}

void game::moveUp(char type, int yCoordinate, int xCoordinate, game::MapShell** map)
{
	if (map[yCoordinate - 1][xCoordinate].passable == true) // ���� ������ ������ ���������
	{
		map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[yCoordinate - 1][xCoordinate].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		map[yCoordinate - 1][xCoordinate].healthPoints =
			map[yCoordinate][xCoordinate].healthPoints;
	}
}

void game::moveDown(char type, int yCoordinate, int xCoordinate, game::MapShell** map)
{
	if (map[yCoordinate + 1][xCoordinate].passable == true) // ���� ������ ����� ��������� 
	{
		map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[yCoordinate + 1][xCoordinate].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		map[yCoordinate + 1][xCoordinate].healthPoints =
			map[yCoordinate][xCoordinate].healthPoints;
	}
}

//------Gravitation_Functions------//
void game::gravity(game::MapShell** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			//���� � ������ ����� � ������ ��� ��� - ���������
			if(map[i][j].type == HERO && map[i + 1][j].passable == true) 
			{
					map[i][j].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
					map[i + 1][j].type = HERO;    // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
					map[i + 1][j].healthPoints =
						map[i][j].healthPoints;
					return;
			}
		}
	}
}

void game::levelOne()
{
	game::clearScreen(); // ������ �����

	game::MapShell** map = game::createMap("Lvl_1.txt"); // ������� ��������� ������ ��������, ��������� ��������� ��������

	game::drawFrame(map); // ������ ������ ����

	game::performAnAction(map); // ��������� ����� � ����������� �� �������� ������
}

//-----Portals_Functions------//
void game::setPortal(char type, int PortalYCoordinate, int PortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::MapShell** map)
{
	if (type == RED_PORTAL)
	{
		PortalXCoordinate = findSomeTypeXCoordinate(RED_PORTAL, map);
		PortalYCoordinate = findSomeTypeYCoordinate(RED_PORTAL, map);

		map[PortalYCoordinate][PortalXCoordinate].type = EMPTY_SPACE;

		map[aimYCoordinate][aimXCoordinate].type = type;

		if (map[aimYCoordinate][aimXCoordinate - 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate - 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}

		else if (map[aimYCoordinate][aimXCoordinate + 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate + 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}
	}

	else if (type == BLUE_PORTAL)
	{
		PortalXCoordinate = findSomeTypeXCoordinate(BLUE_PORTAL, map);
		PortalYCoordinate = findSomeTypeYCoordinate(BLUE_PORTAL, map);

		map[PortalYCoordinate][PortalXCoordinate].type = EMPTY_SPACE;

		map[aimYCoordinate][aimXCoordinate].type = type;

		if (map[aimYCoordinate][aimXCoordinate - 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate - 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}

		else if (map[aimYCoordinate][aimXCoordinate + 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate + 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}
	}
}

//void game::enterThePortal(char type, MapShell** map)
//{
//	
//}