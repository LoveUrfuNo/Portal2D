#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::MapShell** map, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal)
{
	bool gameIsRunning = true; // ��������

	while (gameIsRunning)
	{

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
				moveLeft(AIM_DOT, aim, map);
				break;

			case RIGHT_ARROW:
				moveRight(AIM_DOT, aim, map);
				break;

			case UP_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				moveUp(AIM_DOT, aim, map);
				break;

			case DOWN_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				moveDown(AIM_DOT, aim, map);
				break;

			case SPACE_JUMP:
				jump(hero, map); // ������
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, redPortal, aim, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, bluePortal, aim, map);
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
void game::moveLeft(char type, T* object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate - 1].passable == true) // ���� ������ ����� ��������� 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate][object->xCoordinate - 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
		object->xCoordinate = object->xCoordinate - 1;
	}
}

template <class T>
void game::moveRight(char type, T* object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate + 1].passable == true) // ���� ������ ����� ��������� 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate][object->xCoordinate + 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
		object->xCoordinate = object->xCoordinate + 1;
	}
}

template <class T>
void game::moveUp(char type, T* object, game::MapShell** map)
{
	if (map[object->yCoordinate - 1][object->xCoordinate].passable == true) // ���� ������ ������ ���������
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
		map[object->yCoordinate - 1][object->xCoordinate].type = type;    // ������ ������� ������ �������, � ��� �� ��������� ���� � HP
		object->yCoordinate = object->yCoordinate - 1;
	}
}

template <class T>
void game::moveDown(char type, T* object, game::MapShell** map)
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
	game::RedPortal* redPortal = new RedPortal;
	game::BluePotal* bluePortal = new BluePotal;

	game::clearScreen(); // ������ �����

	game::MapShell** map = game::createMap("Lvl_1.txt", hero, aim, redPortal, bluePortal); // ������� ��������� ������ ��������, ��������� ��������� ��������

	game::drawFrame(map); // ������ ������ ����

	game::performAnAction(map, hero, aim, redPortal, bluePortal); // ��������� ����� � ����������� �� �������� ������
}

//-----Portals_Functions------//
template <class T>
void game::setPortal(char type, T* object, Aim* aim, game::MapShell** map)
{
	if (type == RED_PORTAL)
	{
		map[aim->yCoordinate][aim->xCoordinate].type = type;
		object->xCoordinate = aim->xCoordinate;
		object->yCoordinate = aim->yCoordinate;
	}

	else if (type == BLUE_PORTAL)
	{
		map[aim->yCoordinate][aim->xCoordinate].type = type;
		object->xCoordinate = aim->xCoordinate;
		object->yCoordinate = aim->yCoordinate;
	}
}

//void game::enterThePortal(char type, MapShell** map)
//{
//	
//}