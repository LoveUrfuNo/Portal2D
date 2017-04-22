#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretsAI.h"

//------Moving_Functions------//
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
bool game::performAnAction(GameInfo* gameInfo, MapCell** map)
{
	bool gameIsRunning = true;	// ������� ���������� �����
	bool isMovingRight = true;  // ���������� ��� ������������� ������ (�������� �� ����������� ��������)
	double timeBeforeGame = clock(); // ���������� ��� ����������� �������, ������������ �� ����������� ������
	double timeOnPause = 0.0;	// ���������� ��� �������� ������� �� �����
	int sideOfMovingOx = 0;		// ���������� ��� �������� ����������� �������� � ���������� ����� �� ��� ��
	int sideOfMovingOy = 0;		// ���������� ��� �������� ����������� �������� � ���������� ����� �� ��� ��

	while (gameIsRunning == true)
	{
		if (_kbhit()) // ���� ������ �������
		{
			switch (_getch()) // ������ �������
			{
			case A_LOWER_CASE:
				sideOfMovingOx = -1;
				moveOx(sideOfMovingOx, HERO, gameInfo, map);
				break;

			case D_LOWER_CASE:
				sideOfMovingOx = 1;
				moveOx(sideOfMovingOx, HERO, gameInfo, map);
				break;

			case LEFT_ARROW:
				sideOfMovingOx = -1;
				moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
				break;

			case RIGHT_ARROW:
				sideOfMovingOx = 1;
				moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
				break;

			case UP_ARROW:
				sideOfMovingOy = -1;
				moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
				break;

			case DOWN_ARROW:
				sideOfMovingOy = 1;
				moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
				break;

			case SPACE_JUMP:
				jump(HERO, gameInfo, map);
				break;

			case E_LOWER_CASE:
				setPortal(BLUE_PORTAL, gameInfo, map);
				break;

			case Q_LOWER_CASE:
				setPortal(RED_PORTAL, gameInfo, map);
				break;

			case ENTER:
				enterThePortal(HERO, gameInfo, map);
				activateTheButton(gameInfo, map);
				break;

				/*case R_BUTTON_LOWER_CASE:
					replayceTheAimToHero(gameInfo, map);
					break;*/

			case PAUSE:
				timeOnPause += pause(gameInfo, map);
				break;

			case BACKSPACE:
				gameIsRunning = quitTheLevel(gameInfo, map);
				break;

			default:
				break;
			}
		}

		// ��������� �� ������������ ������
		game::turretAI(STATIONARY_TURRET, gameInfo, map);

		// ��������� �� ������������� ������
		game::turretAI(PLATFORM_TURRET, gameInfo, map);

		// ��������� �� ������ ��������
		game::turretAI(TURRET_HUNTER, gameInfo, map);

		// ��������� ������� ����� ���� (��������� �� ��������, ����� �� ����� �����)
		gameIsRunning = checkGameOverConditions(gameInfo, map, gameIsRunning);

		game::clearScreen(); // ������� �����
		game::drawFrame(map, gameInfo); // ������������ ����
		game::gravity(map, gameInfo); // ��������� ����������
		game::clearScreen(); // ������� �����

		// ���������� ����������� ��� ����������� �������, ������������ �� ����������� ������
		double timeAfterAction = clock() - timeOnPause;

		// ������ ���������� � ����������� �� ����������� ������ ������� (� ��������)
		gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

		if (gameInfo->hero.score > 0)	// ���� ���������� ����� ������ 0, �� ���������� ���� ����
		{
			gameInfo->hero.score -= 1.02354;
		}
	}
	if (gameInfo->hero.healthPoints <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//------Moving_Functions------//
// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::jump(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case HERO:
		// ���� ��� ���������� ���� ������������ ����
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)
		{
			// ���� ��� ������ ��� ������ ���������
			if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				// ���������� ����� �� ��� �� ����������� �� ����
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// �������������� ����

				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);
				// ���������� ����� �� ��� �� ����������� �� ����
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}
			// ���� ��������� ������ ���� ������
			else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);
				// ���������� ����� �� ��� �� ����������� �� ����
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}

		}
		break;

	case TURRET_HUNTER:
		// ���� ��� ������� ���� ������������ ����
		if (map[gameInfo->hunter_turret.yCoordinate + 1][gameInfo->hunter_turret.xCoordinate].passable == false)
		{
			// ���� ��� ������ ��� ������� ���������
			if ((map[gameInfo->hunter_turret.yCoordinate - 1][gameInfo->hunter_turret.xCoordinate].passable == true) &&
				(map[gameInfo->hunter_turret.yCoordinate - 2][gameInfo->hunter_turret.xCoordinate].passable == true))
			{
				//������� ������ ������ �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
				//��������� � ������ ���� ������ ������
				list::addBegin(&map[gameInfo->hunter_turret.yCoordinate - 1][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);

				// ���������� ������ �� ��� �� ����������� �� ����
				gameInfo->hunter_turret.yCoordinate = gameInfo->hunter_turret.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// �������������� ����

				//������� ������ ������ �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
				//��������� � ������ ���� ������ ������
				list::addBegin(&map[gameInfo->hunter_turret.yCoordinate - 1][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
				// ���������� ������ �� ��� �� ����������� �� ����
				gameInfo->hunter_turret.yCoordinate = gameInfo->hunter_turret.yCoordinate - 1;
			}
			// ���� ��������� ������ ���� ������ �� �������
			else if ((map[gameInfo->hunter_turret.yCoordinate - 1][gameInfo->hunter_turret.xCoordinate].passable == true) &&
				(map[gameInfo->hunter_turret.yCoordinate - 2][gameInfo->hunter_turret.xCoordinate].passable == false))
			{
				//������� ������ ������ �� ������� ������
				list::deleteCurrentElement(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
				//��������� � ������ ���� ������ ������
				list::addBegin(&map[gameInfo->hunter_turret.yCoordinate - 1][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
				// ���������� ������ �� ��� �� ����������� �� ����
				gameInfo->hunter_turret.yCoordinate = gameInfo->hunter_turret.yCoordinate - 1;
			}
		}
		break;
	}
}

// ������� ����������� �������� �� ��� Ox
void game::moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + sideOfMovingOx].passable == true &&
			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + sideOfMovingOx].types->value != BUTTON &&
			map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + sideOfMovingOx].types->value != WALL)
		{
			// ������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//��������� � �������� ������ ����� ������ �������
			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + sideOfMovingOx].types, AIM_DOT);
			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + sideOfMovingOx;
		}
		break;

	case HERO:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + sideOfMovingOx].passable == true)
		{
			//������� ������ ����� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//��������� � �������� ������ ����� ������ �����
			list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + sideOfMovingOx].types, HERO);
			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + sideOfMovingOx;
		}
		break;

	case TURRET_HUNTER:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + sideOfMovingOx].passable == true)
		{
			// �� ������� ������ ��������� ������ ������
			list::deleteCurrentElement(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + sideOfMovingOx].types, TURRET_HUNTER);
			gameInfo->hunter_turret.xCoordinate = gameInfo->hunter_turret.xCoordinate + sideOfMovingOx;
		}
		break;

	case STATIONARY_TURRET:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + sideOfMovingOx].passable == true)
		{
			// �� ������� ������ ��������� ������ ������
			list::deleteCurrentElement(&map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate].types, STATIONARY_TURRET);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + sideOfMovingOx].types, STATIONARY_TURRET);
			gameInfo->stationary_turret.xCoordinate = gameInfo->stationary_turret.xCoordinate + sideOfMovingOx;
		}
		break;

	case PLATFORM_TURRET:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + sideOfMovingOx].passable == true)
		{
			// ��������� ������ ������ �� ������� ������
			list::deleteCurrentElement(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + sideOfMovingOx].types, PLATFORM_TURRET);
			gameInfo->platform_turret.xCoordinate = gameInfo->platform_turret.xCoordinate + sideOfMovingOx;
		}
		break;
	}
}

// ������� ����������� �������� �� ��� Oy
void game::moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->aim.yCoordinate + sideOfMovingOy][gameInfo->aim.xCoordinate].passable == true &&
			map[gameInfo->aim.yCoordinate + sideOfMovingOy][gameInfo->aim.xCoordinate].types->value != BUTTON &&
			map[gameInfo->aim.yCoordinate + sideOfMovingOy][gameInfo->aim.xCoordinate].types->value != WALL)
		{
			// ������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			// ��������� � �������� ������ ����� ������ �������
			list::addBegin(&map[gameInfo->aim.yCoordinate + sideOfMovingOy][gameInfo->aim.xCoordinate].types, AIM_DOT);

			gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + sideOfMovingOy;
		}
		break;

	case HERO:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->hero.yCoordinate + sideOfMovingOy][gameInfo->hero.xCoordinate].passable == true)
		{
			// ������� ������ ����� �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			// ��������� �������� � ������ ����� ������ �����
			list::addBegin(&map[gameInfo->hero.yCoordinate + sideOfMovingOy][gameInfo->hero.xCoordinate].types, HERO);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + sideOfMovingOy;
		}
		break;

	case TURRET_HUNTER:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->hunter_turret.yCoordinate + sideOfMovingOy][gameInfo->hunter_turret.xCoordinate].passable == true)
		{
			// ������� ������ ������ �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->hunter_turret.yCoordinate + sideOfMovingOy][gameInfo->hunter_turret.xCoordinate].types, TURRET_HUNTER);

			gameInfo->hunter_turret.yCoordinate = gameInfo->hunter_turret.yCoordinate + sideOfMovingOy;
		}
		break;

	case STATIONARY_TURRET:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->stationary_turret.yCoordinate + sideOfMovingOy][gameInfo->stationary_turret.xCoordinate].passable == true)
		{
			// ������� ������ ������ �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate].types, STATIONARY_TURRET);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->stationary_turret.yCoordinate + sideOfMovingOy][gameInfo->stationary_turret.xCoordinate].types, STATIONARY_TURRET);

			gameInfo->stationary_turret.yCoordinate = gameInfo->stationary_turret.yCoordinate + sideOfMovingOy;
		}
		break;

	case PLATFORM_TURRET:
		// ���� � �������� ������ ���������� ������������
		if (map[gameInfo->platform_turret.yCoordinate + 1][gameInfo->platform_turret.xCoordinate].passable == true)
		{
			// ������� ������ ������ �� ������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);
			// ��������� � �������� ������ ����� ������ ������
			list::addBegin(&map[gameInfo->platform_turret.yCoordinate + sideOfMovingOy][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);

			gameInfo->platform_turret.yCoordinate = gameInfo->platform_turret.yCoordinate + sideOfMovingOy;
		}
		break;
	}
}

void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	int step = 1;
	// ���� � ������ ����� ���� ����� ���������� ������������
	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		// ����������� ����� ���� �� ���� ������ �����
		moveOy(step, HERO, gameInfo, map);
	}
	// ���� � ������ ����� ���� ������ ���������� ������������
	if (map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate].types->value == TURRET_HUNTER &&
		map[gameInfo->hunter_turret.yCoordinate + 1][gameInfo->hunter_turret.xCoordinate].passable == true)
	{
		// ����������� ������ ���� �� ���� ������ �����
		moveOy(step, TURRET_HUNTER, gameInfo, map);
	}
	// ���� � ������ ����� ���� ������ ���������� ������������
	if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate].types->value == STATIONARY_TURRET &&
		map[gameInfo->stationary_turret.yCoordinate + 1][gameInfo->stationary_turret.xCoordinate].passable == true)
	{
		// ����������� ������ ���� �� ���� ������ �����
		moveOy(step, STATIONARY_TURRET, gameInfo, map);
	}

	if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types->value == PLATFORM_TURRET &&
		map[gameInfo->platform_turret.yCoordinate + 1][gameInfo->platform_turret.xCoordinate].passable == true)
	{
		// ����������� ������ ���� �� ���� ������ �����
		moveOy(step, PLATFORM_TURRET, gameInfo, map);
	}
}

// ������� ������� ������, ������� �� ������ ���� ����, ��������� �� ���� �������� ����� � �������
// ���������� ��������� � ������� � ������, ���������� ����� � �������, ����������� �� �����������
records::DataAboutTheChampion* game::startLevel(char* levelName)
{
	game::GameInfo* gameInfo = new GameInfo;
	game::MapCell** map = game::createMap(levelName, gameInfo); // ������� ��������� ������ ��������, ��������� ��������� ��������
	records::DataAboutTheChampion* player = new records::DataAboutTheChampion;

	game::clearScreen(); // ������ �����
	game::drawFrame(map, gameInfo); // ������ ������ ����
	bool playerPassedLevel = game::performAnAction(gameInfo, map); // ��������� ����� � ����������� �� �������� ������

	system("cls");

	if (playerPassedLevel == true || playerPassedLevel == false) // ��� �� ��� �� ��� (� �� ��� �������)
	{
		std::cout << "Please enter your name" << std::endl;

		std::cin >> player->name;

		player->score = gameInfo->hero.score;

		player->level = atoi(&levelName[4]); // ����� ������ ��������� � �������� �� ����� �����

		double score = gameInfo->hero.score;

		std::cout << "\n\n\t\t\tSCORE: " << score << std::endl;
		std::cout << "\t\t\tTIME: " << gameInfo->hero.time << std::endl;
		std::cout << "\n\n\t\t\tPRESS ANY KEY TO CONTINUE" << std::endl;
	}

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
		// ���� ������� ������ ����������
		if (gameInfo->redPortal.yCoordinate != 0)
			// ��������� ������ ������������� �������� �������
			list::deleteCurrentElement(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, RED_PORTAL);
		// ���������� ������ ������� �������������� ����������� �������
		gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate;
		gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

		// � ������ �����, � ������� ��������� ������, ����������� ������ �������� �������
		list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, RED_PORTAL);
	}

	else if (type == BLUE_PORTAL) // ���� �������������� ����� ������
	{
		// ���� ����� ������ ��� ����������
		if (gameInfo->bluePortal.yCoordinate != 0)
			// ��������� ������ ������������� �������� �������
			list::deleteCurrentElement(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, BLUE_PORTAL);
		// ���������� ������ ������� �������������� ����������� �������
		gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;
		gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;
		// � ������ �����, � ������� ��������� ������, ����������� ������ ������ �������
		list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, BLUE_PORTAL);
	}
}

// ������� �������� �� ��������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	// ���� �������� � ������� ������ � ����� ������ ����� � ���������� ����� ������
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0)
	{
		// � ������ ����� �� ����������� ������ ������� ����������� ������ �����
		list::addBegin(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, HERO);
		// �� ������ ����� �� ������� ����������� ����� ��������� ������ �����
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
		// ���������� ����� �������������� � ����������� ������ �������
		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}
	// ���� �������� � ����� ������ � ����� ������ ����� � ���������� ������� ������
	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->redPortal.yCoordinate != 0 && gameInfo->redPortal.xCoordinate != 0)
	{
		// � ������ ����� �� ����������� �������� ������� ����������� ������ �����
		list::addBegin(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, HERO);
		// �� ������ ����� �� ������� ����������� ����� ��������� ������ �����
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
		// ���������� ����� �������������� � ����������� ������ �������
		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
	}
}

//------Button_Functions------//
// ������� ��������� �������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->buttonOne.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->buttonOne.yCoordinate &&	// � ���������� ������������ �����
		map[gameInfo->blackWallOne.yCoordinate][gameInfo->blackWallOne.xCoordinate].types->value == BLACK_WALL)
	{
		// ������ �����, � ������� ���� ������������ �����, ���������� ����������
		map[gameInfo->blackWallOne.yCoordinate][gameInfo->blackWallOne.xCoordinate].passable = true;
		// �� ����� ������������ ����� ������������ ����������
		list::deleteCurrentElement(&map[gameInfo->blackWallOne.yCoordinate][gameInfo->blackWallOne.xCoordinate].types, BLACK_WALL);
		list::deleteCurrentElement(&map[gameInfo->buttonOne.yCoordinate][gameInfo->buttonOne.xCoordinate].types, BUTTON);
	}
	else if (gameInfo->hero.xCoordinate == gameInfo->buttonTwo.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->buttonTwo.yCoordinate &&	// � ���������� ������������ �����
		map[gameInfo->blackWallTwo.yCoordinate][gameInfo->blackWallTwo.xCoordinate].types->value == BLACK_WALL)
	{
		// ������ �����, � ������� ���� ������������ �����, ���������� ����������
		map[gameInfo->blackWallTwo.yCoordinate][gameInfo->blackWallTwo.xCoordinate].passable = true;
		// �� ����� ������������ ����� ������������ ����������
		list::deleteCurrentElement(&map[gameInfo->blackWallTwo.yCoordinate][gameInfo->blackWallTwo.xCoordinate].types, BLACK_WALL);
		list::deleteCurrentElement(&map[gameInfo->buttonTwo.yCoordinate][gameInfo->buttonTwo.xCoordinate].types, BUTTON);
	}
	else if (gameInfo->hero.xCoordinate == gameInfo->buttonThree.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->buttonThree.yCoordinate &&	// � ���������� ������������ �����
		map[gameInfo->blackWallThree.yCoordinate][gameInfo->blackWallThree.xCoordinate].types->value == BLACK_WALL)
	{
		// ������ �����, � ������� ���� ������������ �����, ���������� ����������
		map[gameInfo->blackWallThree.yCoordinate][gameInfo->blackWallThree.xCoordinate].passable = true;
		// �� ����� ������������ ����� ������������ ����������
		list::deleteCurrentElement(&map[gameInfo->blackWallThree.yCoordinate][gameInfo->blackWallThree.xCoordinate].types, BLACK_WALL);
		list::deleteCurrentElement(&map[gameInfo->buttonThree.yCoordinate][gameInfo->buttonThree.xCoordinate].types, BUTTON);
	}
	else if (gameInfo->hero.xCoordinate == gameInfo->buttonFour.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
		gameInfo->hero.yCoordinate == gameInfo->buttonFour.yCoordinate &&	// � ���������� ������������ �����
		map[gameInfo->blackWallFour.yCoordinate][gameInfo->blackWallFour.xCoordinate].types->value == BLACK_WALL)
	{
		// ������ �����, � ������� ���� ������������ �����, ���������� ����������
		map[gameInfo->blackWallFour.yCoordinate][gameInfo->blackWallFour.xCoordinate].passable = true;
		// �� ����� ������������ ����� ������������ ����������
		list::deleteCurrentElement(&map[gameInfo->blackWallFour.yCoordinate][gameInfo->blackWallFour.xCoordinate].types, BLACK_WALL);
		list::deleteCurrentElement(&map[gameInfo->buttonFour.yCoordinate][gameInfo->buttonFour.xCoordinate].types, BUTTON);
	}
}

// ������� ����������� ������� � �����
void game::replayceTheAimToHero(GameInfo* gameInfo, MapCell** map)
{
	// ����������� �������� ������� �� ����������� �����
	list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, AIM_DOT);
	// ��������� ������� �������� �������
	list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
	
	// ����������� ������� ������������� ���������� �����
	gameInfo->aim.xCoordinate = gameInfo->hero.xCoordinate;
	gameInfo->aim.yCoordinate = gameInfo->hero.yCoordinate;
}

// ������� ���������, ��������� �� �������, ��� ������� ���� ������ �����������
bool game::checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning)
{
	if ((gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&	// ���� �������� ��������� � ����� ������ � �������
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate))
	{
		return false;
	}
	else if (gameInfo->hero.healthPoints <= 0) // ���� �������� ������ ���� ��� ����� 0
	{
		return false;
	}
	else if (gameIsRunning == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool game::quitTheLevel(GameInfo* gameInfo, MapCell** map)
{
	std::cout << "\n\n\n\n\n\n\n\n\t   Quit the level?\n\n\t   Press 'y' or 'n'" << std::endl;

	switch (_getch())
	{
	case YES:
		gameInfo->hero.score = 0;
		gameInfo->hero.time = 100000.0;
		return false;
		break;

	case NO:
		drawFrame(map, gameInfo);
		return true;
		break;
	}
}

// ������� �����
double game::pause(GameInfo* gameInfo, MapCell** map)
{
	double startTime = clock();
	std::cout << "\n\n\n\n\n\n\n\n\t       Pause\n\n\t   Press any key" << std::endl;
	_getch();
	system("cls");
	double endTime = clock();
	return endTime - startTime;
}
