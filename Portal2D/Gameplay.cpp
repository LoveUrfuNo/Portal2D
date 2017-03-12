#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(MapCell** map, GameInfo* gameInfo)
{
	bool gameIsRunning = true; // ��������

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
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				moveUp(AIM_DOT, gameInfo, map);
				break;

			case DOWN_ARROW:
				//������� ���� �������� ��������� � ������� ��� ����������, �� ��� ��������, ���� �� �������� ����
				moveDown(AIM_DOT, gameInfo, map);
				break;

			case SPACE_JUMP:
				jump(gameInfo, map); // ������
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
		winLevel(gameInfo, map, gameIsRunning);

		game::clearScreen(); // ������� �����
		game::drawFrame(map, gameInfo);
		game::gravity(map, gameInfo); // ��������� ����������
		Sleep(50);
		game::clearScreen(); // ������� �����

		double timeAfterAction = clock();
		gameInfo->hero.score = (timeAfterAction - timeBeforeGame) / 1000.0;
	}

	double timeAfterGame = clock();

	double requiredTime = (timeAfterGame - timeBeforeGame) / 1000.0;

}

void game::levelOne()
{
	game::GameInfo* gameInfo = new GameInfo;

	game::clearScreen(); // ������ �����

	game::MapCell** map = game::createMap("Lvl_1.txt", gameInfo); // ������� ��������� ������ ��������, ��������� ��������� ��������

	game::drawFrame(map, gameInfo); // ������ ������ ����

	game::performAnAction(map, gameInfo); // ��������� ����� � ����������� �� �������� ������
}

//------Moving_Functions------//

void game::jump(GameInfo* gameInfo, game::MapCell** map)
{
	if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)
	{
		if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // ���� ��� ������ ��� ������ ��������
			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

			game::drawFrame(map, gameInfo);

			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
		}

		else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // ���� �������� ������ ����
			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
		}
	}
}

void game::moveLeft(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].passable == true &&
			peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types) != HERO) // ���� ������ ����� ��������� 
		{
			push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),
				map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types);

			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate - 1;

		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].passable == true &&
			peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types) != AIM_DOT)
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types);

			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
		}
		break;
	}
}

void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].passable == true &&
			peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types) != HERO) // ���� ������ ����� ��������� 
		{
			push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),
				map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types);

			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + 1;

		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].passable == true &&
			peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types) != AIM_DOT)
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types);

			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + 1;
		}
		break;
	}
}

void game::moveUp(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].passable == true &&
		peek(map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types) != HERO) // ���� ������ ����� ��������� 
	{
		push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),
			map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate - 1;

	}
}

void game::moveDown(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].passable == true &&
		peek(map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types) != HERO) // ���� ������ ����� ��������� 
	{
		push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),
			map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + 1;

	}
}

void game::replaceTheAim(char type, GameInfo* gameInfo, game::MapCell** map)
{

	if (peek(map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types) == EMPTY_SPACE)
	{
		moveUp(AIM_DOT, gameInfo, map);
	}

	else if (peek(map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types) == EMPTY_SPACE)
	{
		moveDown(AIM_DOT, gameInfo, map);
	}

	else if (peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types) == EMPTY_SPACE)
	{
		moveRight(AIM_DOT, gameInfo, map);
	}

	else if (peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types) == EMPTY_SPACE)
	{
		moveLeft(AIM_DOT, gameInfo, map);
	}

}

//------Gravitation_Functions------//
void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	if (game::peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types) == HERO && map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
			map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types);

		gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
	}
}

//-----Portals_Functions------//
void game::setPortal(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (type == RED_PORTAL)
	{
		if ((gameInfo->hero.xCoordinate != gameInfo->redPortal.xCoordinate) ||
			(gameInfo->hero.yCoordinate != gameInfo->redPortal.yCoordinate))
		{
			if (gameInfo->redPortal.yCoordinate != 0)
				pop(map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);

			gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate;
			gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

			pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			push(RED_PORTAL, map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);
			push(AIM_DOT, map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			replaceTheAim(AIM_DOT, gameInfo, map);	
		}
	}

	else if (type == BLUE_PORTAL)
	{
		if ((gameInfo->hero.xCoordinate != gameInfo->bluePortal.xCoordinate) ||
			(gameInfo->hero.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->bluePortal.yCoordinate != 0)
				pop(map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);

			gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;
			gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;

			pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			push(BLUE_PORTAL, map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);
			push(AIM_DOT, map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			replaceTheAim(AIM_DOT, gameInfo, map);
		}
	}
}

void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0) 		// ���� ���������� ������ � �������� ������� ���������
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types), map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);
		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}

	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0)
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types), map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);
		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
	}
}

//------Button_Functions------//
void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->button.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->button.yCoordinate)
	{
		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;
		pop(map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].types);
	}
}

bool game::winLevel(GameInfo* gameInfo, MapCell** map, bool& gameIsRunning)
{
	if (gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate)
	{
		gameIsRunning = false;
	}
	return gameIsRunning;
}