#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "Save.h"
#include "TurretAI.h"


//------Moving_Functions------//
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::performAnAction(GameInfo* gameInfo, MapCell** map)
{
	bool gameIsRunning = true;	// ������� ���������� �����

	double timeBeforeGame = clock();

	while (gameIsRunning)
	{

		if (_kbhit()) // ���� ������ �������
		{
			switch (_getch()) // ������ �������
			{
			case A_LOWER_CASE:
				moveLeft(HERO, gameInfo, map);
				break;

			case D_LOWER_CASE:
				moveRight(HERO, gameInfo, map);
				break;

			case LEFT_ARROW:
				moveLeft(AIM_DOT, gameInfo, map);
				break;

			case RIGHT_ARROW:
				moveRight(AIM_DOT, gameInfo, map);
				break;

			case UP_ARROW:
				moveUp(gameInfo, map);
				break;

			case DOWN_ARROW:
				moveDown(AIM_DOT, gameInfo, map);
				break;

			case SPACE_JUMP:
				jump(HERO, gameInfo, map);
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, gameInfo, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, gameInfo, map);
				break;

			case ENTER:
				enterThePortal(HERO, gameInfo, map);
				activateTheButton(gameInfo, map);
				break;

			default:
				break;
			}
		}

		game::turretAI(gameInfo, map);

		// ���� ���������� ����� ����� ����������� ������, �� ���������� gameIsRunning ������������� �������� false
		gameIsRunning = checkGameOverConditions(gameInfo, map);

		game::clearScreen(); // ������� �����
		game::drawFrame(map, gameInfo);
		game::gravity(map, gameInfo); // ��������� ����������
		game::clearScreen(); // ������� �����

		double timeAfterAction = clock();

		gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

		if (gameInfo->hero.score > 0)	// ���� ���������� ����� ������ 0, �� ���������� ���� ����
		{
			gameInfo->hero.score -= 1.02354;
		}
	}

	double timeAfterGame = clock();

	double requiredTime = (timeAfterGame - timeBeforeGame) / 1000.0;
}

//------Moving_Functions------//
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::jump(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case HERO:
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)	// ���� ��� ���������� ���� ������������ ����
		{
			//replaceTheAimMovement(gameInfo, map);

			// ���� ��� ������ ��� ������ ��������
			if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// �������������� ����

				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}

			else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // ���� �������� ������ ����
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == false)	// ���� ��� ���������� ���� ������������ ����
		{
			//replaceTheAimMovement(gameInfo, map);

			// ���� ��� ������ ��� ������ ��������
			if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) &&
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == true))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// �������������� ����

												//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;
			}

			else if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) && // ���� �������� ������ ����
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == false))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;
			}
		}
		break;
	}
}

//// ������� ����������� �����
// ��������� ������ ��������� ��� �������, ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::moveLeft(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{

	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].passable == true)
		{
			// ������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//��������� � ������ ����� ����� ������ �������
			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types, AIM_DOT);
			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate - 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].passable == true)
		{
			//������� ������ ����� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//��������� � ������ ����� ����� ������ �����
			list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types, HERO);
			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
		{
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate - 1;
		}
		break;

	case BULLET:
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
		{
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].types, BULLET);
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate - 1;
		}
		break;
	}
}

// ������� ����������� ����
// ��������� ������ ��������� ��� �������, ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
{

	switch (type)
	{
	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].passable == true)
		{
			//������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//��������� � ������ ����� ������ ������ �������
			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types, AIM_DOT);
			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].passable == true)
		{
			//������� ������ ����� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//��������� � ������ ����� ������ ������ �����
			list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types, HERO);
			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
		{
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate + 1;
		}
		break;

	case BULLET:
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
		{
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].types, BULLET);
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate + 1;
		}
		break;
	}
}

// ������� ����������� ����
// ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::moveUp(GameInfo* gameInfo, game::MapCell** map)
{
	// ���� ������ ����� ����� ��������� � � ��� �� �����
	if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].passable == true)
	{
		//������� ������ ������� �� ������� ������ �����
		list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
		//��������� � ������ ����� ���� ������ �������
		list::addBegin(&map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types, AIM_DOT);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate - 1;
	}
}

// ������� ����������� ����
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::moveDown(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// ���� ����� ������ ����� ��������� � � ��� �� �����
		if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].passable == true)
		{
			//������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//��������� � ������ ����� ���� ������ �������
			list::addBegin(&map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types, AIM_DOT);

			gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
		{
			//������� ������ ����� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//��������� � ������ ����� ���� ������ �����
			list::addBegin(&map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types, HERO);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
		{
			//������� ������ ������ �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			//��������� � ������ ����� ���� ������ ������
			list::addBegin(&map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].types, TURRET);

			gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate + 1;
		}
		break;
	}
}

// ������� ������������ ������, ��� ��������� �������
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::replaceTheAim(GameInfo* gameInfo, game::MapCell** map)
{
	// ���� ����� ����� ������ �����
	if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types->value == EMPTY_SPACE)
	{
		moveRight(AIM_DOT, gameInfo, map);	// ������ ������������� ����� �� ���� ������ �����
	}

	// ���� ����� ����� ����� �����
	else if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types->value == EMPTY_SPACE)
	{
		moveLeft(AIM_DOT, gameInfo, map);	// ������ ������������� ������ �� ���� ������ �����
	}

	// ���� ����� ����� ������ �����
	else if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
	{
		moveUp(gameInfo, map);	// ������ ������������� ����� �� ���� ������ �����
	}

	// ���� ����� ����� ����� �����
	else if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
	{
		moveDown(AIM_DOT, gameInfo, map);	// ������ ������������� ���� �� ���� ������ �����
	}
}

//// ������� ������������ ������, ���� ����� ������ �� ������
//// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
//void game::replaceTheAimMovement(GameInfo* gameInfo, game::MapCell** map)
//{
//	if (peek(map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types) == AIM_DOT)
//	{
//		replaceTheAim(gameInfo, map);
//	}
//
//	else if (peek(map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types) == AIM_DOT)
//	{
//		replaceTheAim(gameInfo, map);
//	}
//}
//
//------Gravitation_Functions------//
// ������� ����������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
//void game::gravity(game::MapCell** map, GameInfo* gameInfo)
//{
//	// ���� ��� ���������� ��� ������������� �����/�������
//	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
//		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
//	{
//		//replaceTheAimMovement(gameInfo, map);
//		Sleep(50);
//		// ����������� ����� ���� �� ���� ������ �����
//		list::addBegin(&map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types, HERO);
//		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
//
//		gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
//	}
//
//	if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types->value == TURRET &&
//		map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
//	{
//		Sleep(50);
//		// ����������� ������ ���� �� ���� ������ �����
//		list::addBegin(&map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].types, TURRET);
//		list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
//
//		gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate + 1;
//	}
//}

void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	// ���� ��� ���������� ��� ������������� �����/�������
	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		//replaceTheAimMovement(gameInfo, map);
		Sleep(50);
		// ����������� ����� ���� �� ���� ������ �����
		moveDown(HERO, gameInfo, map);
	}

	if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types->value == TURRET &&
		map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
	{
		Sleep(50);
		// ����������� ������ ���� �� ���� ������ �����
		moveDown(TURRET, gameInfo, map);
	}
}

// ������� ������� ������, ��������� �� ���� �������� ����� � �������
// ���������� ���������� �����, ��������� �������
records::DataAboutTheChampion* game::startLevel(char* levelName)
{
	game::GameInfo* gameInfo = new GameInfo;

	game::MapCell** map = game::createMap(levelName, gameInfo); // ������� ��������� ������ ��������, ��������� ��������� ��������

	records::DataAboutTheChampion* player = new records::DataAboutTheChampion;

	game::clearScreen(); // ������ �����

	game::drawFrame(map, gameInfo); // ������ ������ ����

	game::performAnAction(gameInfo, map); // ��������� ����� � ����������� �� �������� ������

	system("cls");

	std::cout << "Please enter your name" << std::endl;

	std::cin >> player->name;

	player->score = gameInfo->hero.score;

	player->level = atoi(&levelName[4]);

	double score = gameInfo->hero.score;

	std::cout << "\n\n\t\t\tSCORE: " << score << std::endl;
	std::cout << "\t\t\tTIME: " << gameInfo->hero.time << std::endl;
	std::cout << "\n\n\t\t\tPRESS ANY KEY TO CONTINUE" << std::endl;

	_getch();

	game::freeMemory(map, gameInfo); // ������� ������� ������

	game::clearScreen(); // ������ �����

	return player;
}

//-----Portals_Functions------//
// ������� ��������� ������� �������
// ��������� �� ���� ������ �������, ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::setPortal(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (type == RED_PORTAL)	// ���� �������������� ������� ������
	{
		if ((gameInfo->aim.xCoordinate != gameInfo->bluePortal.xCoordinate) ||
			(gameInfo->aim.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->redPortal.yCoordinate != 0)	// ���� ������� ������ ��� ����, �� ������������ ������� ������ ��������
				list::deleteCurrentElement(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, RED_PORTAL);

			gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate; // ���������� ������ ������� �������������� ����������� �������
			gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, RED_PORTAL);
			//replaceTheAim(gameInfo, map);	// ������ ��������� � �������
		}
	}

	else if (type == BLUE_PORTAL) // ���� �������������� ����� ������
	{
		if ((gameInfo->aim.xCoordinate != gameInfo->bluePortal.xCoordinate) ||
			(gameInfo->aim.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->bluePortal.yCoordinate != 0)	// ���� ����� ������ ��� ����, �� ������������ ����� ������ ��������
				list::deleteCurrentElement(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, BLUE_PORTAL);

			gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;	// ���������� ������ ������� �������������� ����������� �������
			gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;

			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, BLUE_PORTAL);
			//replaceTheAim(gameInfo, map);	// ������ ��������� � �������
		}
	}
}

// ������� �������� �� ��������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&	// ���� �������� � ������� ������ � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0) // � ������ ������ ����������
	{
		list::addBegin(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, HERO);
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);

		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}
	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate && // ���� �������� � ����� ������ � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->redPortal.yCoordinate != 0 && gameInfo->redPortal.xCoordinate != 0)	// � ������ ������ ����������
	{
		list::addBegin(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, HERO);
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);	// ����� ������������ �� ����������� ������� �������
		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
	}
}

//------Button_Functions------//
// ������� ��������� �������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->button.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->button.yCoordinate)
	{
		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;// ������������ ����� ���������� ����������
		list::deleteCurrentElement(&map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].types, BLACK_WALL);	// �� ����� ������������ ����� ������������ ����������
	}
}

bool game::checkGameOverConditions(GameInfo* gameInfo, MapCell** map)
{
	if ((gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&	// ���� �������� ��������� � ����� ������ � �������
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate) ||
		(gameInfo->hero.healthPoints <= 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}