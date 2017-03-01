#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::MapShell** map)
{
	int redPortalXCoordinate = 0;
	int redPortalYCoordinate = 0;
	int bluePortalXCoordinate = 0;
	int bluePortalYCoordinate = 0;

	bool gameIsRunning = true; // ��������

	while (gameIsRunning)
	{
		int heroXCoordinate = findHeroXCoordinate(map); //���� ���������� ����� �� ��� X
		int heroYCoordinate = findHeroYCoordinate(map); //���� ���������� ����� �� ��� Y

		int aimXCoordinate = findAimXCoordinate(map); //���� ���������� ������� �� ��� X
		int aimYCoordinate = findAimYCoordinate(map); //���� ���������� ������� �� ��� X

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
				moveLeft(AIM_DOT, heroYCoordinate, heroXCoordinate, map);
				break;

			case RIGHT_ARROW:
				moveRight(AIM_DOT, heroYCoordinate, heroXCoordinate, map);
				break;

			case UP_ARROW:
				moveUp(AIM_DOT, heroYCoordinate, heroXCoordinate, map);
				break;

			case DOWN_ARROW:
				moveDown(AIM_DOT, heroYCoordinate, heroXCoordinate, map);
				break;

			case SPACE_JUMP:
				jump(heroYCoordinate, heroXCoordinate, map); // ������
				break;

				/*case E_LOWER_CASE:
					redPortalXCoordinate = aimXCoordinate;
					redPortalYCoordinate = aimYCoordinate;
					setRedPortal(RED_PORTAL, redPortalYCoordinate, redPortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
					break;*/

					/*case Q_LOWER_CASE:
						bluePortalXCoordinate = aimXCoordinate;
						bluePortalYCoordinate = aimYCoordinate;
						setBluePortal(BLUE_PORTAL, redPortalYCoordinate, redPortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
						break;*/

			default:
				break;
			}
		}
		game::clearScreen(); // ������� �����
		game::drawFrame(map);
		game::gravity(map); // ��������� ����������
		Sleep(100);
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

		drawFrame(map);

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
/*void game::setRedPortal(char type, int redPortalYCoordinate, int redPortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = RED_PORTAL;
	map[redPortalYCoordinate][redPortalXCoordinate].type = EMPTY_SPACE;

	if (map[aimYCoordinate][aimXCoordinate - 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate - 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}

	else if (map[aimYCoordinate][aimXCoordinate + 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate + 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}
	redPortalXCoordinate = aimXCoordinate;
	redPortalYCoordinate = aimYCoordinate;
}
void game::setBluePortal(char type, int bluePortalYCoordinate, int bluePortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = BLUE_PORTAL;
	map[bluePortalYCoordinate][bluePortalXCoordinate].type = EMPTY_SPACE;

	if (map[aimYCoordinate][aimXCoordinate - 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate - 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}

	else if (map[aimYCoordinate][aimXCoordinate + 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate + 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}
	bluePortalXCoordinate = aimXCoordinate;
	bluePortalYCoordinate = aimYCoordinate;
}*/