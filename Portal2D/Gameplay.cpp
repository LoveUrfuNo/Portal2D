#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretsAI.h"

namespace game
{
	// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void performAnAction(GameInfo* gameInfo, MapCell** map)
	{
		bool gameIsRunning = true;	// ������� ���������� �����
		double timeBeforeGame = clock(); // ���������� ��� ����������� �������, ������������ �� ����������� ������
		double timeOnPause = 0.0;	// ���������� ��� �������� ������� �� �����
		int sideOfMovingOx;		// ���������� ��� �������� ����������� �������� � ���������� ����� �� ��� ��
		int sideOfMovingOy;		// ���������� ��� �������� ����������� �������� � ���������� ����� �� ��� ��

		while (gameIsRunning == true)
		{
			if (_kbhit()) // ���� ������ �������
			{
				switch (_getch()) // ������ �������
				{
				case A_LOWER_CASE: case A_LOWER_CASE_RU: case A_UPPER_CASE: case A_UPPER_CASE_RU:
					sideOfMovingOx = STEP_LEFT_OR_UP;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case D_LOWER_CASE: case D_LOWER_CASE_RU: case D_UPPER_CASE: case D_UPPER_CASE_RU:
					sideOfMovingOx = STEP_RIGHT_OR_DOWN;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case LEFT_ARROW:
					sideOfMovingOx = STEP_LEFT_OR_UP;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case RIGHT_ARROW:
					sideOfMovingOx = STEP_RIGHT_OR_DOWN;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case UP_ARROW:
					sideOfMovingOy = STEP_LEFT_OR_UP;
					moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
					break;

				case DOWN_ARROW:
					sideOfMovingOy = STEP_RIGHT_OR_DOWN;
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
					enterThePortal(gameInfo, map);
					activateTheButton(gameInfo, map);
					break;

				case PAUSE_LOWER_CASE: case PAUSE_LOWER_CASE_RU:
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
				gameInfo->hero.score -= SCORE_PER_SECOND;
			}
		}
	}

	//------Moving_Functions------//

	// ������� ����������� �������� �� ��� Ox
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, MapCell** map)
	{
		// ���� ����������� �� ��� Ox ��������
		if (isMovingPossibleOx(getCoordinates(gameInfo, type), map, sideOfMovingOx, type))
		{
			// ������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// ��������� � �������� ������ ����� ������ �������
			list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].types, type);
			// �������� ���������� ������� �� Ox
			changeOXCoordinates(gameInfo, type, sideOfMovingOx);

		}
	}

	// ������� ����������� �������� �� ��� Oy
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, MapCell** map)
	{
		// ���� ����������� �� ��� Oy ��������
		if (isMovingPossibleOy(getCoordinates(gameInfo, type), map, sideOfMovingOy, type))
		{
			// ������� ������ ������� �� ������� ������ �����
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// ��������� � �������� ������ ����� ������ �������
			list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// �������� ���������� ������� �� Oy
			changeOYCoordinates(gameInfo, type, sideOfMovingOy);
		}
	}

	// ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void jump(char type, GameInfo* gameInfo, MapCell** map)
	{
		// ���� ��� �������� ���� ������������ ����
		if (isObjectStandingOnTheFloor(getCoordinates(gameInfo, type), map))
		{
			// ���� ��� ������ ��� �������� ���������
			if (bothCellsAboveTheObjectAreFree(getCoordinates(gameInfo, type), map))
			{
				// ������� ������ ������� �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ��������� � ������ ���� ������ �������
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);

				// ���������� ������� �� ��� �� ����������� �� ����
				changeOYCoordinates(gameInfo, type, STEP_LEFT_OR_UP);
				// �������������� ����
				drawFrame(map, gameInfo);

				// ������� ������ ������� �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ��������� � ������ ���� ������ �������
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ���������� ������� �� ��� �� ����������� �� ����
				changeOYCoordinates(gameInfo, type, JUMP_HEIGHT);
			}
			// ���� ��� �������� ��������� ������ ���� ������
			else if (oneCellAboveTheObjectIsFree(getCoordinates(gameInfo, type), map))
			{
				// ������� ������ ������ �� ������� ������
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ��������� � ������ ���� ������ �������
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// ���������� ������� �� ��� �� ����������� �� ����
				changeOYCoordinates(gameInfo, type, JUMP_HEIGHT);
			}

		}
	}

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapCell** map, GameInfo* gameInfo)
	{
		// ���� � ������ ����� ���� ����� ���������� ������������
		if (map[getCoordinates(gameInfo, HERO).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, HERO).xCoordinate].passable == true)
		{
			// ����������� ����� ���� �� ���� ������ �����
			moveOy(STEP_RIGHT_OR_DOWN, HERO, gameInfo, map);
		}
		// ���� � ������ ����� ���� ������-�������� ���������� ������������
		if (map[getCoordinates(gameInfo, TURRET_HUNTER).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, TURRET_HUNTER).xCoordinate].passable == true)
		{
			// ����������� ������-�������� ���� �� ���� ������ �����
			moveOy(STEP_RIGHT_OR_DOWN, TURRET_HUNTER, gameInfo, map);
		}
		// ���� � ������ ����� ���� ������������ ������ ���������� ������������
		if (map[getCoordinates(gameInfo, STATIONARY_TURRET).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, STATIONARY_TURRET).xCoordinate].passable == true)
		{
			// ����������� ������������ ������ ���� �� ���� ������ �����
			moveOy(STEP_RIGHT_OR_DOWN, STATIONARY_TURRET, gameInfo, map);
		}
		// ���� � ������ ����� ���� ������������� ������ ���������� ������������
		if (map[getCoordinates(gameInfo, PLATFORM_TURRET).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, PLATFORM_TURRET).xCoordinate].passable == true)
		{
			// ����������� ������������� ������ ���� �� ���� ������ �����
			moveOy(STEP_RIGHT_OR_DOWN, PLATFORM_TURRET, gameInfo, map);
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
		// ���� ������ ����������
		if (getCoordinates(gameInfo, type).yCoordinate != 0)
		{
			// ������� ������ �������
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
		}
		// ������������� ���������� ������� �� ��� Ox
		setOXCoordinates(gameInfo, type, NO_STEP);
		// ������������� ���������� ������� �� ��� Oy
		setOYCoordinates(gameInfo, type);
		// ��������� ������ �������
		list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
	}

	// ������� �������� �� ��������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void enterThePortal(GameInfo* gameInfo, MapCell** map)
	{
		// ���������� ��� �������� ���� �������
		char typeOfPortal = findTypeOfPortal(gameInfo);
		// ���� ����� ����� � �������
		if (typeOfPortal != NULL)
		{
			// ��������� ������ ����� �� ����������� ������� �������
			list::addBegin(&map[getCoordinates(gameInfo, typeOfPortal).yCoordinate][getCoordinates(gameInfo, typeOfPortal).xCoordinate].types, HERO);
			// ������� ������ ����� �� ����������� ���������
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, HERO).yCoordinate][getCoordinates(gameInfo, HERO).xCoordinate].types, HERO);

			// ������������� ���������� ����� �� ����������� ������� �������
			gameInfo->hero.coordinates.xCoordinate = getCoordinates(gameInfo, typeOfPortal).xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = getCoordinates(gameInfo, typeOfPortal).yCoordinate;
		}
	}

	// ������� ���������� ��� �������, � ������� ����� ��������� �����������
	char findTypeOfPortal(GameInfo* gameInfo)
	{
		// ���������� ��� �������� ���� �������, � ������� ����� ��������� �����������
		char typeOfPortal = NULL;
		// ���� ����� � ������� �������
		if (getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, RED_PORTAL).xCoordinate &&
			getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, RED_PORTAL).yCoordinate &&
			getCoordinates(gameInfo, BLUE_PORTAL).yCoordinate != 0 && getCoordinates(gameInfo, BLUE_PORTAL).xCoordinate != 0)
		{
			typeOfPortal = BLUE_PORTAL;
		}
		// ���� ����� � ����� �������
		else if (getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, BLUE_PORTAL).xCoordinate &&
			getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, BLUE_PORTAL).yCoordinate &&
			getCoordinates(gameInfo, RED_PORTAL).yCoordinate != 0 && getCoordinates(gameInfo, RED_PORTAL).xCoordinate != 0)
		{
			typeOfPortal = RED_PORTAL;
		}

		return typeOfPortal;
	}

	//------Button_Functions------//

	// ������� ��������� �������, ��������� ��������� � ����������� �� ������� �� ����� � ��������� ������ ��������
	void activateTheButton(GameInfo* gameInfo, MapCell** map)
	{
		// ���������� ��� �������� ���� �����
		char typeOfDoor = findTypeOfDoor(gameInfo, map);
		// ���������� ��� �������� ���� ������
		char typeOfButton = findTypeOfButton(typeOfDoor);
		// ���� ������ ���������� � ����� ����� �� ������
		if (typeOfDoor != NULL)
		{
			// ������ ����� �� ����������� ����� ���������� ����������
			map[getCoordinates(gameInfo, typeOfDoor).yCoordinate][getCoordinates(gameInfo, typeOfDoor).xCoordinate].passable = true;
			// ������� ������ �����
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, typeOfDoor).yCoordinate][getCoordinates(gameInfo, typeOfDoor).xCoordinate].types, typeOfDoor);
			// ������� ������ ������
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, typeOfButton).yCoordinate][getCoordinates(gameInfo, typeOfButton).xCoordinate].types, typeOfButton);
		}
	}

	// ������� ���������� ��� �����
	char findTypeOfDoor(GameInfo* gameInfo, MapCell** map)
	{
		// ���������� ��� �������� ���� �����
		char typeOfDoor = NULL;
		// ���� ����� ����� �� ������, ������� ��������� ������ �����
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonOne.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonOne.coordinates.yCoordinate &&
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types->value == BLACK_WALL_ONE_S)
		{
			typeOfDoor = BLACK_WALL_ONE_S;
		}
		// ���� ����� ����� �� ������, ������� ��������� ������ �����
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonTwo.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonTwo.coordinates.yCoordinate &&
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types->value == BLACK_WALL_TWO_S)
		{
			typeOfDoor = BLACK_WALL_TWO_S;
		}
		// ���� ����� ����� �� ������, ������� ��������� ������ �����
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonThree.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonThree.coordinates.yCoordinate &&
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types->value == BLACK_WALL_THREE_S)
		{
			typeOfDoor = BLACK_WALL_THREE_S;

		}
		// ���� ����� ����� �� ������, ������� ��������� �������� �����
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonFour.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonFour.coordinates.yCoordinate &&
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types->value == BLACK_WALL_FOUR_S)
		{
			typeOfDoor = BLACK_WALL_FOUR_S;
		}
		return typeOfDoor;
	}

	// ������� ���������� ��� ������
	char findTypeOfButton(char typeOfDoor)
	{
		// ���������� ��� �������� ���� ������
		char typeOfButton = NULL;
		switch (typeOfDoor)
		{
		case BLACK_WALL_ONE_S:
			typeOfButton = BUTTON_ONE_S;
			break;

		case BLACK_WALL_TWO_S:
			typeOfButton = BUTTON_TWO_S;
			break;

		case BLACK_WALL_THREE_S:
			typeOfButton = BUTTON_THREE_S;
			break;

		case BLACK_WALL_FOUR_S:
			typeOfButton = BUTTON_FOUR_S;
			break;
		}

		return typeOfButton;
	}

	//------Auxiliary_Functions------//

	// ������� ���������, ��������� �� �������, ��� ������� ���� ������ �����������
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning)
	{
		// ���� �������� ��������� � ����� ������ � �������
		if ((getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, EXIT).xCoordinate) &&
			(getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, EXIT).yCoordinate))
		{
			return false;
		}
		// ���� �������� ������ ���� ��� ����� 0
		else if (gameInfo->hero.healthPoints <= 0)
		{
			gameInfo->hero.isPlayerPassedLevel = false;
			return false;
		}
		// ���� ��� ��������� ����� �� ����
		else if (gameIsRunning == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// ������� ��������� ������� ����
	bool quitTheLevel(GameInfo* gameInfo, MapCell** map)
	{
		std::cout << "\n\n\n\n\n\n\n\n\t   Quit the level?\n\n\t   Press 'y' or 'n'" << std::endl;
		// ���������� ��� �������� ������ ������ (����� ��� ��� �� ����)
		bool isPlayerWantsToQuitLevel = false;
		switch (_getch())
		{
			// ���� ����� ������������ �����
		case YES_LOWER_CASE: case YES_LOWER_CASE_RU: case YES_UPPER_CASE: case YES_UPPER_CASE_RU:
			gameInfo->hero.isPlayerPassedLevel = false;
			isPlayerWantsToQuitLevel = true;
			break;
			// ���� ����� �������� �����
		case NO_LOWER_CASE: case NO_LOWER_CASE_RU: case NO_UPPER_CASE: case NO_UPPER_CASE_RU:
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

	// ������� ��������� ����� �� ������ �� ������������ �����������
	bool isObjectStandingOnTheFloor(Coordinates coordinates, MapCell** map)
	{
		// ���� ��� �������� ��������
		if (map[coordinates.yCoordinate + STEP_RIGHT_OR_DOWN][coordinates.xCoordinate].passable == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ������� ��������� ���� �� ��� �������� ��� ��������� ������
	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map)
	{
		// ���� ��� ������ ��� �������� ���������
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

	// ������� ��������� ���� �� ��� �������� ���� ��������� ������
	bool oneCellAboveTheObjectIsFree(Coordinates coordinates, MapCell** map)
	{
		// ���� ���� ������ ��� �������� ���������
		if ((map[coordinates.yCoordinate - 1][coordinates.xCoordinate].passable == true) &&
			(map[coordinates.yCoordinate - 2][coordinates.xCoordinate].passable == false))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ������� ��������� ����������� ������������ �� ��� Ox
	bool isMovingPossibleOx(Coordinates coordinates, MapCell** map, int sideOfMovingOx, char type)
	{
		// ���� �� ��� Ox ���������� ������������
		// ���� �����(������) �� ������� ��� ������ ��� ����� (� ������ ����������� �������) 
		if ((type == AIM_DOT && map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].passable == true &&
			map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].types->value != BUTTON &&
			map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].types->value != WALL) ||
			(type != AIM_DOT && map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ������� ��������� ����������� ������������ �� ��� Oy
	bool isMovingPossibleOy(Coordinates coordinates, MapCell** map, int sideOfMovingOy, char type)
	{
		// ���� �� ��� Oy ���������� ������������
		// ���� ������(�����) �� ������� ��� ������ ��� ����� (� ������ ����������� �������) 
		if ((type == AIM_DOT && map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].passable == true &&
			map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].types->value != BUTTON &&
			map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].types->value != WALL) ||
			(type != AIM_DOT && map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ������� ���������� ���������� �������
	Coordinates getCoordinates(GameInfo* gameInfo, char type)
	{
		// ���������� ��� �������� ������� ��������� �������
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

		case BULLET_OF_STATIONARY_TURRET:
			requiredCoords = gameInfo->bulletOfStationaryTurret.coordinates;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			requiredCoords = gameInfo->bulletOfPlatformTurret.coordinates;
			break;

		case BULLET_OF_HUNTER_TURRET:
			requiredCoords = gameInfo->bulletOfHunterTurret.coordinates;
			break;

		case BLACK_WALL_ONE_S:
			requiredCoords = gameInfo->blackWallOne.coordinates;
			break;

		case BLACK_WALL_TWO_S:
			requiredCoords = gameInfo->blackWallTwo.coordinates;
			break;

		case BLACK_WALL_THREE_S:
			requiredCoords = gameInfo->blackWallThree.coordinates;
			break;

		case BLACK_WALL_FOUR_S:
			requiredCoords = gameInfo->blackWallFour.coordinates;
			break;

		case BUTTON_ONE_S:
			requiredCoords = gameInfo->buttonOne.coordinates;
			break;

		case BUTTON_TWO_S:
			requiredCoords = gameInfo->buttonTwo.coordinates;
			break;

		case BUTTON_THREE_S:
			requiredCoords = gameInfo->buttonThree.coordinates;
			break;

		case BUTTON_FOUR_S:
			requiredCoords = gameInfo->buttonFour.coordinates;
			break;

		case EXIT:
			requiredCoords = gameInfo->exitFromLevel.coordinates;
			break;

		default:
			break;
		}

		return requiredCoords;
	}

	// ������� �������� ���������� ������� �� ��� Ox
	void changeOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx)
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

		case BULLET_OF_STATIONARY_TURRET:
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		case BULLET_OF_HUNTER_TURRET:
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		default:
			break;
		}
	}

	// ������� �������� ���������� ������� �� ��� Oy
	void changeOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy)
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

		default:
			break;
		}
	}

	// ������� ������������� ���������� ������� �� ��� Ox
	void setOXCoordinates(GameInfo* gameInfo, char type, int step)
	{
		switch (type)
		{
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			break;

		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			break;

		case BULLET_OF_STATIONARY_TURRET:
			// ���� ������������ ������ ��������
			if (step != NO_STEP)
			{
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->stationary_turret.coordinates.xCoordinate + step;
			}
			// ���� ������������ ������ �� ��������
			else
			{
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		case BULLET_OF_PLATFORM_TURRET:
			// ���� ������������� ������ ��������
			if (step != NO_STEP)
			{
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->platform_turret.coordinates.xCoordinate + step;
			}
			// ���� ������������� ������ �� ��������
			else
			{
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		case BULLET_OF_HUNTER_TURRET:
			// ���� ������-������� ��������
			if (step != NO_STEP)
			{
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->hunter_turret.coordinates.xCoordinate + step;
			}
			// ���� ������-������� �� ��������
			else
			{
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		default:
			break;
		}
	}

	// ������� ������������� ���������� ������� �� ��� Oy
	void setOYCoordinates(GameInfo* gameInfo, char type)
	{
		switch (type)
		{
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			break;

		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			break;

		case BULLET_OF_STATIONARY_TURRET:
			gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate = gameInfo->stationary_turret.coordinates.yCoordinate;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate = gameInfo->platform_turret.coordinates.yCoordinate;
			break;

		case BULLET_OF_HUNTER_TURRET:
			gameInfo->bulletOfHunterTurret.coordinates.yCoordinate = gameInfo->hunter_turret.coordinates.yCoordinate;
			break;

		default:
			break;
		}
	}
}