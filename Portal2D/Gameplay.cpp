#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::MapShell** map, Hero* hero, Aim* aim, RedPotal* redPortal, BluePotal* bluePortal)
{
	bool gameIsRunning = true; // ��������

	while (gameIsRunning)
	{
		//int heroXCoordinate = findSomeTypeXCoordinate(HERO, map); //���� ���������� ����� �� ��� X
		//int heroYCoordinate = findSomeTypeYCoordinate(HERO, map); //���� ���������� ����� �� ��� Y

		int PortalXCoordinate = findSomeTypeXCoordinate(RED_PORTAL, map);
		int PortalYCoordinate = findSomeTypeYCoordinate(RED_PORTAL, map);

		//int aimXCoordinate = findSomeTypeXCoordinate(AIM_DOT, map); //���� ���������� ������� �� ��� X
		//int aimYCoordinate = findSomeTypeYCoordinate(AIM_DOT, map); //���� ���������� ������� �� ��� Y

		if (_kbhit()) // ���� ������ �������
		{
			switch (_getch()) // ������ �������
			{
			case A_LOWER_CASE:
				moveLeft(HERO, hero, map);
				break;

			case D_LOWER_CASE:
				moveRight(HERO, hero, map);
				break;

			case LEFT_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aim->yCoordinate][aim->xCoordinate - 1].type != RED_PORTAL) && (map[aim->yCoordinate][aim->xCoordinate - 1].type != BLUE_PORTAL))
					moveLeft(AIM_DOT, aim, map);
				break;

			case RIGHT_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aim->yCoordinate][aim->xCoordinate + 1].type != RED_PORTAL) && (map[aim->yCoordinate][aim->xCoordinate + 1].type != BLUE_PORTAL))
					moveRight(AIM_DOT, aim, map);
				break;

			case UP_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				if ((map[aim->yCoordinate - 1][aim->xCoordinate].type != RED_PORTAL) && (map[aim->yCoordinate - 1][aim->xCoordinate].type != BLUE_PORTAL))
					moveUp(AIM_DOT, aim, map);
				break;

			case DOWN_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
					if ((map[aim->yCoordinate + 1][aim->xCoordinate].type != RED_PORTAL) && (map[aim->yCoordinate + 1][aim->xCoordinate].type != BLUE_PORTAL))
				moveDown(AIM_DOT, aim, map);
				break;

			case SPACE_JUMP:
				jump(hero, map); // ������
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, PortalYCoordinate, PortalXCoordinate, aim->yCoordinate, aim->xCoordinate, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, PortalYCoordinate, PortalXCoordinate, aim->yCoordinate, aim->xCoordinate, map);
				break;

			/*case ENTER:
				
				break;*/

			default:
				break;
			}
		}
		game::clearScreen(); // ������� �����
		game::drawFrame(map);
		game::gravity(map, hero); // ��������� ����������
		Sleep(50);
		game::clearScreen(); // ������� �����
	}
}

void game::jump(Hero* hero, game::MapShell** map)
{
	if (map[hero->yCoordinate + 1][hero->xCoordinate].passable == false)
	{
		if ((map[hero->yCoordinate - 1][hero->xCoordinate].passable == true) && // ���� ��� ������ ��� ������ ��������
			(map[hero->yCoordinate - 2][hero->xCoordinate].passable == true))
		{
			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ����� ������� ������, � ������
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;	  // ���� ������� ������ �����, � ��� �� ��������� ���� � HP
			hero->yCoordinate = hero->yCoordinate - 1;

			game::drawFrame(map);

			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE;
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;
			hero->yCoordinate = hero->yCoordinate - 1;
		}

		else if ((map[hero->yCoordinate - 1][hero->xCoordinate].passable == true) && // ���� �������� ������ ����
			(map[hero->yCoordinate - 2][hero->xCoordinate].passable == false))
		{
			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE;
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;
			hero->yCoordinate = hero->yCoordinate - 1;
		}
	}
}

template <class T>
void game::moveLeft(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate - 1].passable == true) // ���� ������ ����� ��������� 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate][object->xCoordinate - 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
		object->xCoordinate = object->xCoordinate - 1;
	}
}

template <class T>
void game::moveRight(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate + 1].passable == true) // ���� ������ ����� ��������� 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate][object->xCoordinate + 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
		object->xCoordinate = object->xCoordinate + 1;
	}
}
template <class T>
void game::moveUp(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate - 1][object->xCoordinate].passable == true) // ���� ������ ������ ���������
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate - 1][object->xCoordinate].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		object->yCoordinate = object->yCoordinate - 1;
	}
}

template <class T>
void game::moveDown(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate + 1][object->xCoordinate].passable == true) // ���� ������ ����� ��������� 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate + 1][object->xCoordinate].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		object->yCoordinate = object->yCoordinate + 1;
	}
}

//------Gravitation_Functions------//
template <class T>
void game::gravity(game::MapShell** map, T *object)
{
	if (map[object->yCoordinate][object->xCoordinate].type == HERO && map[object->yCoordinate + 1][object->xCoordinate].passable == true)
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE;
		map[object->yCoordinate + 1][object->xCoordinate].type = HERO;
		object->yCoordinate = object->yCoordinate + 1;
	}
}

//void game::gravity(game::MapShell** map)
//{
//	for (int i = 0; i < MAP_HEIGHT; i++)
//	{
//		for (int j = 0; j < MAP_WIDTH; j++)
//		{
//			//���� � ������ ����� � ������ ��� ��� - ���������
//			if(map[i][j].type == HERO && map[i + 1][j].passable == true) 
//			{
//					map[i][j].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//					map[i + 1][j].type = HERO;    // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//					map[i + 1][j].healthPoints =
//						map[i][j].healthPoints;
//					return;
//			}
//		}
//	}
//}

void game::levelOne()
{
	game::Hero* hero = new Hero;
	game::Aim* aim = new Aim;
	game::RedPotal* redPortal = new RedPotal;
	game::BluePotal* bluePortal = new BluePotal;

	game::clearScreen(); // ������ �����

	game::MapShell** map = game::createMap("Lvl_1.txt", hero, aim, redPortal, bluePortal); // ������� ��������� ������ ��������, ��������� ��������� ��������

	game::drawFrame(map); // ������ ������ ����

	game::performAnAction(map, hero, aim, redPortal, bluePortal); // ��������� ����� � ����������� �� �������� ������
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