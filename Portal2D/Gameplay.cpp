#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretsAI.h"

namespace game
{
	//------Moving_Functions------//
	// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void performAnAction(GameInfo* gameInfo, MapCell** map)
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
				case A_LOWER_CASE: case A_LOWER_CASE_RU: case A_UPPER_CASE: case A_UPPER_CASE_RU:
					sideOfMovingOx = -1;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case D_LOWER_CASE: case D_LOWER_CASE_RU: case D_UPPER_CASE: case D_UPPER_CASE_RU:
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

				case E_LOWER_CASE: case E_LOWER_CASE_RU: case E_UPPER_CASE: case E_UPPER_CASE_RU:
					setPortal(BLUE_PORTAL, gameInfo, map);
					break;

				case Q_LOWER_CASE: case Q_LOWER_CASE_RU: case Q_UPPER_CASE: case Q_UPPER_CASE_RU:
					setPortal(RED_PORTAL, gameInfo, map);
					break;

				case ENTER:
					enterThePortal(HERO, gameInfo, map);
					activateTheButton(gameInfo, map);
					break;

				case PAUSE_LOWER_CASE: case PAUSE_LOWER_CASE_RU: // ��� ���-�� �� ���
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
			turretAI(STATIONARY_TURRET, gameInfo, map);

			// ��������� �� ������������� ������
			turretAI(PLATFORM_TURRET, gameInfo, map);

			// ��������� �� ������ ��������
			turretAI(TURRET_HUNTER, gameInfo, map);

			// ��������� ������� ����� ���� (��������� �� ��������, ����� �� ����� �����)
			gameIsRunning = checkGameOverConditions(gameInfo, map, gameIsRunning);

			clearScreen(); // ������� �����
			drawFrame(map, gameInfo); // ������������ ����
			gravity(map, gameInfo); // ��������� ����������
			clearScreen(); // ������� �����

								 // ���������� ����������� ��� ����������� �������, ������������ �� ����������� ������
			double timeAfterAction = clock() - timeOnPause;

			// ������ ���������� � ����������� �� ����������� ������ ������� (� ��������)
			gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

			if (gameInfo->hero.score > 0)	// ���� ���������� ����� ������ 0, �� ���������� ���� ����
			{
				gameInfo->hero.score -= 1.02354;
			}
		}
	}

	//------Moving_Functions------//
	// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void jump(char type, GameInfo* gameInfo, MapCell** map)
	{
		// ���� ��� ���������� ���� ������������ ����
		if (objectIsStandingOnTheFloor(getCoordinates(gameInfo, type), map))
		{
			// ���� ��� ������ ��� �������� ���������
			if (bothCellsAboveTheObjectAreFree(getCoordinates(gameInfo, type), map))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);

				// ���������� ����� �� ��� �� ����������� �� ����
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 �������������

				drawFrame(map, gameInfo);	// �������������� ����

												//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ���������� ����� �� ��� �� ����������� �� ����
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 �������������
			}
			// ���� ��������� ������ ���� ������
			else if ((map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].passable == true) &&
				(map[getCoordinates(gameInfo, type).yCoordinate - 2][getCoordinates(gameInfo, type).xCoordinate].passable == false))
			{
				//������� ������ ����� �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//��������� � ������ ���� ������ �����
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ���������� ����� �� ��� �� ����������� �� ����
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 �������������
			}

		}
	}

	// ������� ����������� �������� �� ��� Ox
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == AIM_DOT)
		{
			// ���� � �������� ������ ���������� ������������
			if (map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].passable == true &&
				map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types->value != BUTTON &&
				map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types->value != WALL)
			{
				// ������� ������ ������� �� ������� ������ �����
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//��������� � �������� ������ ����� ������ �������
				list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types, type);
				setOXCoordinates(gameInfo, type, sideOfMovingOx);
			}
		}

		else
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].passable == true)
			{
				//������� ������ ����� �� ������� ������ �����
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//��������� � �������� ������ ����� ������ �����
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].types, type);
				setOXCoordinates(gameInfo, type, sideOfMovingOx);
			}
		}
	
	}


	// ������� ����������� �������� �� ��� Oy
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == AIM_DOT)
		{
			// ���� � �������� ������ ���������� ������������
			if (map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].passable == true &&
				map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].types->value != BUTTON &&
				map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].types->value != WALL)
			{
				// ������� ������ ������� �� ������� ������ �����
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ��������� � �������� ������ ����� ������ �������
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);

				setOYCoordinates(gameInfo, type, sideOfMovingOy);
			}
		}
		
		else
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].passable == true)
			{
				// ������� ������ ������� �� ������� ������ �����
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ��������� � �������� ������ ����� ������ �������
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);

				setOYCoordinates(gameInfo, type, sideOfMovingOy);
			}
		}	
	}

	void gravity(MapCell** map, GameInfo* gameInfo)
	{
		int step = 1;
		// ���� � ������ ����� ���� ����� ���������� ������������
		if (map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types->value == HERO &&
			map[gameInfo->hero.coordinates.yCoordinate + 1][gameInfo->hero.coordinates.xCoordinate].passable == true)
		{
			// ����������� ����� ���� �� ���� ������ �����
			moveOy(step, HERO, gameInfo, map);
		}
		// ���� � ������ ����� ���� ������ ���������� ������������
		if (map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate].types->value == TURRET_HUNTER &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate + 1][gameInfo->hunter_turret.coordinates.xCoordinate].passable == true)
		{
			// ����������� ������ ���� �� ���� ������ �����
			moveOy(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� � ������ ����� ���� ������ ���������� ������������
		if (map[gameInfo->stationary_turret.coordinates.yCoordinate][gameInfo->stationary_turret.coordinates.xCoordinate].types->value == STATIONARY_TURRET &&
			map[gameInfo->stationary_turret.coordinates.yCoordinate + 1][gameInfo->stationary_turret.coordinates.xCoordinate].passable == true)
		{
			// ����������� ������ ���� �� ���� ������ �����
			moveOy(step, STATIONARY_TURRET, gameInfo, map);
		}

		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate].types->value == PLATFORM_TURRET &&
			map[gameInfo->platform_turret.coordinates.yCoordinate + 1][gameInfo->platform_turret.coordinates.xCoordinate].passable == true)
		{
			// ����������� ������ ���� �� ���� ������ �����
			moveOy(step, PLATFORM_TURRET, gameInfo, map);
		}
	}

	// ������� ������� ������, ������� �� ������ ���� ����, ��������� �� ���� �������� ����� � �������
	// ���������� ��������� � ������� � ������, ���������� ����� � �������, ����������� �� �����������
	records::DataAboutTheChampion* startLevel(char* levelName)
	{
		GameInfo* gameInfo = new GameInfo;
		MapCell** map = createMap(levelName, gameInfo); // ������� ��������� ������ ��������, ��������� ��������� ��������
		records::DataAboutTheChampion* player = new records::DataAboutTheChampion;
		clearScreen(); // ������ �����
		drawFrame(map, gameInfo); // ������ ������ ����
		performAnAction(gameInfo, map); // ��������� ����� � ����������� �� �������� ������
		system("cls");


		if (gameInfo->hero.isPlayerPassedLevel == true)
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
		else
		{
			player->isPlayerPassedLevel = false;
			std::cout << "\n\n\t\t\tEND OF GAME" << std::endl;
		}

		_getch();

		freeMemory(map, gameInfo); // ������� ������� ������

		clearScreen(); // ������ �����

		return player;
	}

	//-----Portals_Functions------//
	// ������� ��������� ������� �������
	// ��������� �� ���� ������ �������, ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void setPortal(char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == RED_PORTAL)	// ���� �������������� ������� ������
		{
			// ���� ������� ������ ����������
			if (gameInfo->redPortal.coordinates.yCoordinate != 0)
				// ��������� ������ ������������� �������� �������
				list::deleteCurrentElement(&map[gameInfo->redPortal.coordinates.yCoordinate][gameInfo->redPortal.coordinates.xCoordinate].types, RED_PORTAL);
			// ���������� ������ ������� �������������� ����������� �������
			gameInfo->redPortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			gameInfo->redPortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;

			// � ������ �����, � ������� ��������� ������, ����������� ������ �������� �������
			list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, RED_PORTAL);
		}

		else if (type == BLUE_PORTAL) // ���� �������������� ����� ������
		{
			// ���� ����� ������ ��� ����������
			if (gameInfo->bluePortal.coordinates.yCoordinate != 0)
				// ��������� ������ ������������� �������� �������
				list::deleteCurrentElement(&map[gameInfo->bluePortal.coordinates.yCoordinate][gameInfo->bluePortal.coordinates.xCoordinate].types, BLUE_PORTAL);
			// ���������� ������ ������� �������������� ����������� �������
			gameInfo->bluePortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			gameInfo->bluePortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			// � ������ �����, � ������� ��������� ������, ����������� ������ ������ �������
			list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, BLUE_PORTAL);
		}
	}

	// ������� �������� �� ��������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
	{
		// ���� �������� � ������� ������ � ����� ������ ����� � ���������� ����� ������
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->redPortal.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->redPortal.coordinates.yCoordinate &&
			gameInfo->bluePortal.coordinates.yCoordinate != 0 && gameInfo->bluePortal.coordinates.xCoordinate != 0)
		{
			// � ������ ����� �� ����������� ������ ������� ����������� ������ �����
			list::addBegin(&map[gameInfo->bluePortal.coordinates.yCoordinate][gameInfo->bluePortal.coordinates.xCoordinate].types, HERO);
			// �� ������ ����� �� ������� ����������� ����� ��������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, HERO);
			// ���������� ����� �������������� � ����������� ������ �������
			gameInfo->hero.coordinates.xCoordinate = gameInfo->bluePortal.coordinates.xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = gameInfo->bluePortal.coordinates.yCoordinate;
		}
		// ���� �������� � ����� ������ � ����� ������ ����� � ���������� ������� ������
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->bluePortal.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->bluePortal.coordinates.yCoordinate &&
			gameInfo->redPortal.coordinates.yCoordinate != 0 && gameInfo->redPortal.coordinates.xCoordinate != 0)
		{
			// � ������ ����� �� ����������� �������� ������� ����������� ������ �����
			list::addBegin(&map[gameInfo->redPortal.coordinates.yCoordinate][gameInfo->redPortal.coordinates.xCoordinate].types, HERO);
			// �� ������ ����� �� ������� ����������� ����� ��������� ������ �����
			list::deleteCurrentElement(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, HERO);
			// ���������� ����� �������������� � ����������� ������ �������
			gameInfo->hero.coordinates.xCoordinate = gameInfo->redPortal.coordinates.xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = gameInfo->redPortal.coordinates.yCoordinate;
		}
	}

	//------Button_Functions------//
	// ������� ��������� �������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void activateTheButton(GameInfo* gameInfo, MapCell** map)
	{
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonOne.coordinates.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonOne.coordinates.yCoordinate &&	// � ���������� ������������ �����
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ������ �����, � ������� ���� ������������ �����, ���������� ����������
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].passable = true;
			// �� ����� ������������ ����� ������������ ����������
			list::deleteCurrentElement(&map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonOne.coordinates.yCoordinate][gameInfo->buttonOne.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonTwo.coordinates.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonTwo.coordinates.yCoordinate &&	// � ���������� ������������ �����
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ������ �����, � ������� ���� ������������ �����, ���������� ����������
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].passable = true;
			// �� ����� ������������ ����� ������������ ����������
			list::deleteCurrentElement(&map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonTwo.coordinates.yCoordinate][gameInfo->buttonTwo.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonThree.coordinates.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonThree.coordinates.yCoordinate &&	// � ���������� ������������ �����
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ������ �����, � ������� ���� ������������ �����, ���������� ����������
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].passable = true;
			// �� ����� ������������ ����� ������������ ����������
			list::deleteCurrentElement(&map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonThree.coordinates.yCoordinate][gameInfo->buttonThree.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonFour.coordinates.xCoordinate &&	// ���� �������� � ������ ��������� � ����� ������
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonFour.coordinates.yCoordinate &&	// � ���������� ������������ �����
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ������ �����, � ������� ���� ������������ �����, ���������� ����������
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].passable = true;
			// �� ����� ������������ ����� ������������ ����������
			list::deleteCurrentElement(&map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonFour.coordinates.yCoordinate][gameInfo->buttonFour.coordinates.xCoordinate].types, BUTTON);
		}
	}

	// ������� ����������� ������� � �����
	void replayceTheAimToHero(GameInfo* gameInfo, MapCell** map)
	{
		// ����������� �������� ������� �� ����������� �����
		list::addBegin(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, AIM_DOT);
		// ��������� ������� �������� �������
		list::deleteCurrentElement(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, AIM_DOT);

		// ����������� ������� ������������� ���������� �����
		gameInfo->aim.coordinates.xCoordinate = gameInfo->hero.coordinates.xCoordinate;
		gameInfo->aim.coordinates.yCoordinate = gameInfo->hero.coordinates.yCoordinate;
	}

	// ������� ���������, ��������� �� �������, ��� ������� ���� ������ �����������
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning)
	{
		if ((gameInfo->hero.coordinates.xCoordinate == gameInfo->exitFromLevel.coordinates.xCoordinate &&	// ���� �������� ��������� � ����� ������ � �������
			gameInfo->hero.coordinates.yCoordinate == gameInfo->exitFromLevel.coordinates.yCoordinate))
		{
			return false;
		}
		else if (gameInfo->hero.healthPoints <= 0) // ���� �������� ������ ���� ��� ����� 0
		{
			gameInfo->hero.isPlayerPassedLevel = false;
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

	bool quitTheLevel(GameInfo* gameInfo, MapCell** map)
	{
		std::cout << "\n\n\n\n\n\n\n\n\t   Quit the level?\n\n\t   Press 'y' or 'n'" << std::endl;
		bool isPlayerWantsToQuitLevel = false;
		switch (_getch())
		{
		case YES_LOWER_CASE:
			gameInfo->hero.isPlayerPassedLevel = false;
			isPlayerWantsToQuitLevel = true;
			break;

		case NO_LOWER_CASE:
			drawFrame(map, gameInfo);
			isPlayerWantsToQuitLevel = false;
			break;

		}
		return !isPlayerWantsToQuitLevel;
	}

	// ������� �����
	double pause(GameInfo* gameInfo, MapCell** map)
	{
		double startTime = clock();
		std::cout << "\n\n\n\n\n\n\n\n\t       Pause\n\n\t   Press any key" << std::endl;
		_getch();
		system("cls");
		double endTime = clock();
		return endTime - startTime;
	}

	bool objectIsStandingOnTheFloor(Coordinates coordinates, MapCell** map)
	{
		if (map[coordinates.yCoordinate + 1][coordinates.xCoordinate].passable == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map)
	{
		if ((map[coordinates.yCoordinate - 1][coordinates.xCoordinate].passable == true) &&
			(map[coordinates.yCoordinate - 2][coordinates.xCoordinate].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Coordinates getCoordinates(GameInfo* gameInfo, char type)
	{
		Coordinates requiredCoords;

		switch (type)
		{
		case HERO:
			requiredCoords = gameInfo->hero.coordinates;
			break;
		case AIM_DOT:
			requiredCoords = gameInfo->aim.coordinates;
			break;
		case TURRET_HUNTER:
			requiredCoords = gameInfo->hunter_turret.coordinates;
			break;
		case STATIONARY_TURRET:
			requiredCoords = gameInfo->stationary_turret.coordinates;
			break;
		case PLATFORM_TURRET:
			requiredCoords = gameInfo->platform_turret.coordinates;
			break;
		case RED_PORTAL:
			requiredCoords = gameInfo->redPortal.coordinates;
			break;
		case BLUE_PORTAL:
			requiredCoords = gameInfo->bluePortal.coordinates;
			break;
		default:
			break;
		}

		return requiredCoords;
	}

	void setOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx)
	{
		switch (type)
		{
		case HERO:
			gameInfo->hero.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case AIM_DOT:
			gameInfo->aim.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case TURRET_HUNTER:
			gameInfo->hunter_turret.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case PLATFORM_TURRET:
			gameInfo->platform_turret.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.xCoordinate += sideOfMovingOx;
			break;
		default:
			break;
		}
	}

	void setOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy)
	{
		switch (type)
		{
		case HERO:
			gameInfo->hero.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case AIM_DOT:
			gameInfo->aim.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case TURRET_HUNTER:
			gameInfo->hunter_turret.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case PLATFORM_TURRET:
			gameInfo->platform_turret.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.yCoordinate += sideOfMovingOy;
			break;
		default:
			break;
		}
	}
}