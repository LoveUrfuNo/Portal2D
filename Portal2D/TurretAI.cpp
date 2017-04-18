#include "TurretAI.h"
#include "Map.h"
#include "Definitions.h"

void game::stationaryTurret(GameInfo* gameInfo, MapCell** map)
{
	int step = determinePositionOfHero(gameInfo, map);
	bool turretCanShootingToHero = checkTurretShotConditions(gameInfo, map, step);
	shootingToHero(gameInfo, map, turretCanShootingToHero, step);
	//platformTurretPatrol(gameInfo, map, step);
}

int game::determinePositionOfHero(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate > gameInfo->stationary_turret.xCoordinate)
	{
		return 1;
	}
	else if (gameInfo->hero.xCoordinate < gameInfo->stationary_turret.xCoordinate)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

bool game::checkTurretShotConditions(GameInfo* gameInfo, MapCell** map, int step)
{
	if (step != 0)
	{
		int wallIsHere = false;
		int searcher = gameInfo->stationary_turret.xCoordinate;
		while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
		{
			if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].passable == true)
			{
				searcher = searcher + step;
			}
			else
			{
				wallIsHere = true;
			}
		}
		return !wallIsHere;
	}
}

void game::shootingToHero(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step)
{
	if (turretCanShootingToHero == true || gameInfo->bullet.xCoordinate != 0)
	{
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + step].passable == true &&
			gameInfo->bullet.xCoordinate == 0)
		{
			gameInfo->bullet.xCoordinate = gameInfo->stationary_turret.xCoordinate + step;
			gameInfo->bullet.yCoordinate = gameInfo->stationary_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
		}

		else if (gameInfo->bullet.xCoordinate != 0)
		{
			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				// ���� ��������
				gameInfo->bullet.xCoordinate = 0;
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].passable == true)
			{
				moveBullet(gameInfo, map, step);
			}

			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].passable == false)
			{
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				// ���� ��������
				gameInfo->bullet.xCoordinate = 0;
			}
		}

		else
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
		}
	}
}

void game::moveBullet(GameInfo* gameInfo, MapCell** map, int step)
{
	// � ������ ����� ����������� ������ ������
	list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].types, BULLET);
	// �� ������� ������ ��������� ������ ������
	list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
	gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate + step;
}

//void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, int step)
//{
//	if (step == 0)
//	{
//
//	}
//}



































//// ������� �������� �� ������ �� ������
//void game::turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight)
//{
//	//bool heroIsSpotted = spottingHeroPatrol(gameInfo, map);
//	// ���������� ������ � ���� ���������� � ������� ����� ����� ������� � ������
//	// true - ����� ����, false - ����� ���
//	bool wallIsHere = checkTheWall(gameInfo, map);
//	//����������� ������� �������������� ������
//	turretPatrol(gameInfo, map, isMovingRight, &wallIsHere);
//	// ����������� ������� �������� ������
//	shootingToHeroPatrol(gameInfo, map, &wallIsHere);
//}
//
//// ������� ���������, ���� �� ����� ������ � ������� �����
//bool game::checkTheWall(GameInfo* gameInfo, MapCell** map)
//{
//	// ���� ����� � ������ ��������� �� ����� ������, � ����� ��������� ������
//	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
//		gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//	{
//		// ����� ���� ����� ������ � �������
//		for (int i = gameInfo->platform_turret.xCoordinate; i < gameInfo->hero.xCoordinate; i++)
//		{
//			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
//			{
//				return true; // ���� ����� ������� - ������������ ������� true
//			}
//		}
//	}
//	// ���� ����� � ������ ��������� �� ����� ������, � ����� ��������� �����
//	else if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
//		gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//	{
//		// ����� ���� ����� ������ � ������
//		for (int i = gameInfo->platform_turret.xCoordinate; i > gameInfo->hero.xCoordinate; i--)
//		{
//			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
//			{
//				return true; // ���� ����� ������� - ������������ ������� true
//			}
//		}
//	}
//	return false;	// ���� ����� �� ������� - ������������ ������� false
//}
//
//// ������� �������� �� �������� �� �����
//void game::shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool *wallIsHere)
//{
//	// �������� �������� ������ ���� ����� ������ � ������� ����������� �����
//	if (*wallIsHere == false && gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
//	{
//		// ���� ����� ������ ������
//		if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//		{
//			// ���� ���� ���������� � ������ �� ������ ���������� ������������
//			if (gameInfo->bullet.xCoordinate == 0 &&
//				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true)
//			{
//				// ������ �� ������ ���������� ����
//				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate + 1;
//				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
//				// ������ �� ������ ���������� �������� ����
//				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			}
//		}
//		// ���� ����� ����� ������
//		else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//		{
//			// ���� ���� �� ���������� � ����� �� ������ ���������� ������������
//			if (gameInfo->bullet.xCoordinate == 0 &&
//				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true)
//			{
//				// ����� �� ������ ���������� ����
//				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate - 1;
//				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
//				// ����� �� ������ ���������� �������� ����
//				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			}
//		}
//		// ���� ����� � ������ � ����� ������
//		else if ((gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate) &&
//			(gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
//		}
//	}
//	// ���� ����� ��������� ������
//	if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//	{
//		shootingRight(gameInfo, map);	// ������ �������� ������
//	}
//
//	// ���� ����� ��������� �����
//	else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//	{
//		shootingLeft(gameInfo, map);	// ������ �������� �����
//	}
//}
//
//// �������� �� �������� ������
//void game::shootingRight(GameInfo* gameInfo, MapCell** map)
//{
//	// ���� ���� ����������
//	if (gameInfo->bullet.xCoordinate != 0)
//	{
//		// ���� ���������� ���� � ������ ���������
//		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
//			(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
//			// ��������� �������� ����
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// ���� ��������
//			gameInfo->bullet.xCoordinate = 0;
//		}
//		// ���� ������ �� ���� ���������� ������������
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
//		{
//			moveRight(BULLET, gameInfo, map);	//���� ������������ ������
//		}
//		// ���� ������ �� ���� ������������ ������������
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == false)
//		{
//			// �������� ���� ��������
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// ���� ��������
//			gameInfo->bullet.xCoordinate = 0;
//		}
//	}
//}
//
//// �������� �� �������� �����
//void game::shootingLeft(GameInfo* gameInfo, MapCell** map)
//{
//	// ���� ���� ����������
//	if (gameInfo->bullet.xCoordinate != 0)
//	{
//		// ���� ���������� ���� � ������ ���������
//		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
//			(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
//			// ��������� �������� ����
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// ���� ��������
//			gameInfo->bullet.xCoordinate = 0;
//		}
//		// ���� ����� �� ���� ���������� ������������
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
//		{
//			moveLeft(BULLET, gameInfo, map); // ���� ������������ �����
//		}
//		// ���� ����� �� ���� ������������ ������������
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == false)
//		{
//			// ��������� �������� ����
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// ���� ��������
//			gameInfo->bullet.xCoordinate = 0;
//		}
//	}
//}
//
//// �������� �� �������������� ��������� �������
//void game::turretPatrol(GameInfo* gameInfo, MapCell** map, bool *isMovingRight, bool *isWallHere)
//{
//	// ���� ����� ������� � ������� ���� ����� ��� ������ � ����� ��������� �� ������ ������
//	if (*isWallHere == true ||
//		gameInfo->hero.yCoordinate != gameInfo->platform_turret.yCoordinate)
//	{
//		// ���� ������ �� ������ ��������� ������������ � ������ ��������� ������
//		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && *isMovingRight == true)
//		{
//			moveRight(PLATFORM_TURRET, gameInfo, map); // ������ ������������ ������
//			*isMovingRight = true; // ������� ����������� �������� - ������
//		}
//		// ���� ������ �� ������ ��������� ������������ � ������ ��������� ����� 
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && *isMovingRight == false)
//		{
//			moveLeft(PLATFORM_TURRET, gameInfo, map); // ������ ������������ �����
//			*isMovingRight = false; // ������� ����������� �������� - �����
//		}
//		// ���� ������ �� ������ ������������ ������������
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
//		{
//			*isMovingRight = false;	// ������� ����������� �������� - �����
//			moveLeft(PLATFORM_TURRET, gameInfo, map);	//������ ������������ �����
//		}
//		// ���� ����� �� ������ ������������ ������������
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
//		{
//			*isMovingRight = true;	// ������� ����������� �������� - ������
//			moveRight(PLATFORM_TURRET, gameInfo, map);
//		}
//	}
//}



















/*


			TURRET HUNTER BELOW


*/

//void game::turretAI(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	heroIsSpotted = spottingHero(gameInfo, map);
//	turretMoving(gameInfo, map, heroIsSpotted);
//	shootingToHero(gameInfo, map, heroIsSpotted);
//}

//// ������� ���������, ��������� �� ����� � ���� ��������� ������
//bool game::spottingHeroPatrol(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
//	{
//		return true;
//	}
//	return false;
//}

//void game::turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
//{
//	if (heroIsSpotted == true)
//	{
//		if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
//		{
//			moveRight(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
//		{
//			//jump(TURRET_EASY, gameInfo, map);
//			moveRight(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
//		{
//			moveLeft(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
//		{
//			//jump(TURRET_EASY, gameInfo, map);
//			moveLeft(TURRET_EASY, gameInfo, map);
//		}
//	}
//}

//bool game::spottingHero(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	for (int i = gameInfo->turret.xCoordinate - HERO_SPOTTING_RANGE_X; i < gameInfo->turret.xCoordinate + HERO_SPOTTING_RANGE_X; i++)
//	{
//		for (int j = gameInfo->turret.yCoordinate + HERO_SPOTTING_RANGE_Y; j > gameInfo->turret.yCoordinate - HERO_SPOTTING_RANGE_Y; j--)
//		{
//			if ((gameInfo->hero.xCoordinate == i) && (gameInfo->hero.yCoordinate == j))
//			{
//				return heroIsSpotted = true;
//			}
//		}
//	}
//	return false;
//}

//void game::shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
//{
//	if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate)
//	{
//		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
//		{
//			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate + 1;
//			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
//			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//
//		}
//		else if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
//		{
//			turretMoving(gameInfo, map, heroIsSpotted);
//		}
//
//		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
//		{
//			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//			{
//				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
//			{
//				moveRight(BULLET, gameInfo, map);
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == false)
//			{
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//		}
//	}
//	else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate)
//	{
//		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
//		{
//			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate - 1;
//			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
//			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//
//		}
//
//		else if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
//		{
//			turretMoving(gameInfo, map, heroIsSpotted);
//		}
//
//		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
//		{
//			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//			{
//				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
//			{
//				moveLeft(BULLET, gameInfo, map);
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == false)
//			{
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//		}
//	}
//	else if ((gameInfo->hero.xCoordinate == gameInfo->turret.xCoordinate) && (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate))
//	{
//		gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//	}
//}