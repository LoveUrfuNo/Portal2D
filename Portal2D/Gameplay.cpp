#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(MapCell** map, GameInfo* gameInfo)
{
	bool gameIsRunning = true; // ��������

	while (gameIsRunning)
	{

		if (_kbhit()) // ���� ������ �������
		{
			switch (_getch()) // ������ �������
			{
			case A_LOWER_CASE:
				moveLeft(HERO, gameInfo, map);
				break;

			//case D_LOWER_CASE:
			//	moveRight(HERO, gameInfo, map);
			//	break;

			//case LEFT_ARROW:
			//	moveLeft(AIM_DOT, gameInfo, map);
			//	break;

			//case RIGHT_ARROW:
			//	moveRight(AIM_DOT, gameInfo, map);
			//	break;

			//case UP_ARROW:
			//	//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
			//	moveUp(AIM_DOT, gameInfo, map);
			//	break;

			//case DOWN_ARROW:
			//	//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
			//	moveDown(AIM_DOT, gameInfo, map);
			//	break;

			//case SPACE_JUMP:
			//	jump(gameInfo, map); // ������
			//	break;

			//case E_LOWER_CASE:
			//	setPortal(RED_PORTAL, gameInfo, map);
			//	break;

			//case Q_LOWER_CASE:
			//	setPortal(BLUE_PORTAL, gameInfo, map);
			//	break;

			//case ENTER:
			//	enterThePortal(HERO, gameInfo, map);
			//	activateTheButton(gameInfo, map);
			//	break;

			default:
				break;
			}
		}
		game::clearScreen(); // ������� �����
		game::drawFrame(map);
		//game::gravity(map, gameInfo); // ��������� ����������
		Sleep(50);
		game::clearScreen(); // ������� �����
	}
}

//void game::jump(GameInfo* gameInfo, game::MapCell** map)
//{
//	if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)
//	{
//		if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // ���� ��� ������ ��� ������ ��������
//			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
//		{
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ����� ������� ������, � ������
//			map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].type = HERO;	  // ���� ������� ������ �����, � ��� �� ��������� ���� � HP
//			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
//
//			game::drawFrame(map);
//
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE;
//			map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].type = HERO;
//			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
//		}
//
//		else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // ���� �������� ������ ����
//			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
//		{
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE;
//			map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].type = HERO;
//			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
//		}
//	}
//}

void game::moveLeft(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].passable == true) // ���� ������ ����� ��������� 
		{
			push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),
				map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types);

			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate - 1;

			//map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
			//map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP

		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].passable == true)
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types);

			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
			//map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
			//map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
			//gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
		}
		break;
	}
}

//void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
//{
//	switch (type)
//	{
//	case AIM_DOT:
//		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].passable == true) // ���� ������ ����� ��������� 
//		{
//			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + 1;
//		}
//		break;
//
//	case HERO:
//		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].passable == true)
//		{
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + 1;
//		}
//		break;
//	}
//}
//
//void game::moveUp(char type, GameInfo* gameInfo, game::MapCell** map)
//{
//	switch (type)
//	{
//	case AIM_DOT:
//		if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].passable == true) // ���� ������ ����� ��������� 
//		{
//			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate - 1;
//		}
//		break;
//
//	case HERO:
//		if (map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true)
//		{
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
//		}
//		break;
//	}
//}
//
//void game::moveDown(char type, GameInfo* gameInfo, game::MapCell** map)
//{
//	switch (type)
//	{
//	case AIM_DOT:
//		if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].passable == true) // ���� ������ ����� ��������� 
//		{
//			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + 1;
//		}
//		break;
//
//	case HERO:
//		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
//		{
//			map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE; // � ������, ��� ��� ������ ������� ������, � ������
//			map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].type = type;	  // ����� ������� ������ �������, � ��� �� ��������� ���� � HP
//			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
//		}
//		break;
//	}
//}
//
////------Gravitation_Functions------//
//void game::gravity(game::MapCell** map, GameInfo* gameInfo)
//{
//	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type == HERO && map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
//	{
//		map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE;
//		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].type = HERO;
//		gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
//	}
//}
//
void game::levelOne()
{
	game::GameInfo* gameInfo = new GameInfo;

	game::clearScreen(); // ������ �����

	game::MapCell** map = game::createMap("Lvl_1.txt", gameInfo); // ������� ��������� ������ ��������, ��������� ��������� ��������

	game::drawFrame(map); // ������ ������ ����

	game::performAnAction(map, gameInfo); // ��������� ����� � ����������� �� �������� ������
}
//
////-----Portals_Functions------//
//void game::setPortal(char type, GameInfo* gameInfo, game::MapCell** map)
//{
//	if (type == RED_PORTAL)
//	{
//		map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = type;
//		gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate;
//		gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;
//	}
//	else if (type == BLUE_PORTAL)
//	{
//		map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].type = type;
//		gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;
//		gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;
//	}
//}
//void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
//{
//	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&	// ���� ������������
//		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate)		// ���� ���������� ������ � �������� ������� ���������
//	{
//		map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE;
//		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
//		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
//		map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = HERO;
//	}
//
//	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate &&
//		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate)
//	{
//		map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = EMPTY_SPACE;
//		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
//		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
//		map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].type = HERO;
//	}
//}
//
////------Button_Functions------//
//void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
//{
//	if (gameInfo->hero.xCoordinate == gameInfo->button.xCoordinate &&
//		gameInfo->hero.yCoordinate == gameInfo->button.yCoordinate)
//	{
//		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;
//		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].type = EMPTY_SPACE;
//	}
//}