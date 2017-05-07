#include "TurretsAI.h"
#include "Map.h"
#include "Definitions.h"

// ������� ������� �� �������, ��������� �� ������
void game::turretAI(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET && gameInfo->stationary_turret.coordinates.xCoordinate != 0)
	{
		// step - ���������� ��� �������� ����������� �������� � ����������� 
		int step = determineMovingDirection(STATIONARY_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(STATIONARY_TURRET, gameInfo, map, step);
		shootHero(STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootHero, step);
		shootHero(PLATFORM_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootHero, step);
		shootHero(TURRET_HUNTER, gameInfo, map, turretCanShootHero, step);
	}
}

// ���������� ����������� �������� �������� (���� � �������), ����������� �� ��������� �����
int game::determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map)
{
	// ���������� ��� �������� ����������� �������� (���������� ������ ������ �� ���������)
	int direction = NO_STEP;

	if (type == STATIONARY_TURRET)
	{
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->stationary_turret.coordinates.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->stationary_turret.coordinates.xCoordinate)
		{
			direction = STEP_LEFT_UP;
		}
	}

	else if (type == PLATFORM_TURRET)
	{
		if (gameInfo->hero.coordinates.xCoordinate >= gameInfo->platform_turret.coordinates.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else
		{
			direction = STEP_LEFT_UP;
		}
	}

	else if (type == TURRET_HUNTER)
	{
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate)
		{
			direction = STEP_LEFT_UP;
		}
	}

	return direction;
}

// ���������, ������ �� ������ ��������
bool game::checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	bool turretCanShoot = false;
	bool wallIsHere = false;
	if (type == STATIONARY_TURRET)
	{
		// ���������� ��� ������ ����� 
		int searcher = gameInfo->stationary_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->stationary_turret.coordinates.yCoordinate)
		{
			// ���� ���������� ����� �� ����� ����������� ������ � ��� �����
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				// ���� �� ����������� ������ ��������� �����
				if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					// � ����������� ������ ����������� ���
					searcher = searcher + step;
				}
				// ���� �� ����������� ������ ��� �����
				else if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				// ���� �� ����������� ������ ���� �����
				else if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}

			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		int searcher = gameInfo->platform_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->platform_turret.coordinates.yCoordinate)
		{
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}
			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}
	else if (type == TURRET_HUNTER)
	{
		int searcher = gameInfo->hunter_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->hunter_turret.coordinates.yCoordinate)
		{
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}
			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}

	return turretCanShoot;
}

// ������� ���������� ��������� ���� (�� ���������, ������������)
void game::shootHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	if (type == STATIONARY_TURRET)
	{
		// ���� � �����(������) ���������� ������������ � �� ���������� ���� � ������ ����� ��������
		if (map[gameInfo->stationary_turret.coordinates.yCoordinate][gameInfo->stationary_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// ������(�����) �������� ����
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->stationary_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate = gameInfo->stationary_turret.coordinates.yCoordinate;
			// ������(�����) �������� �������� ����
			list::addBegin(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		}

		// ���� ���� ���������� � �������� �����������
		else if (gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// ���� ���������� ���� � ����� ���������
			if ((gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// ���� ��������
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = 0;
			}
			// ���� ������(�����) �� ���� ���������� ������������
			else if (map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].passable == true)
			{
				// ���� ������������
				moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].passable == false)
			{
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// ���� ��������
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = 0;
			}
		}
		// ���� ����������� �� ��������� � ����� �� ����� ������ � �������
		else if (step == NO_STEP && gameInfo->hero.coordinates.yCoordinate == gameInfo->stationary_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
		}
		// ���� ����� ��� �� ����� ���� � ���� ����������
		else if (turretCanShootHero == false && gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate != 0)
		{
			// ���� ������������
			moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		// ���� � �����(������) ���������� ������������ � �� ���������� ���� � ������ ����� ��������
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// ������(�����) �������� ����
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->platform_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate = gameInfo->platform_turret.coordinates.yCoordinate;
			// ������(�����) �������� �������� ����
			list::addBegin(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		}
		
		// ���� ���� ���������� � �������� �����������
		else if (gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// ���� ���������� ���� � ����� ���������
			if ((gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// ���� ��������
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = 0;
			}
			// ���� ������(�����) �� ���� ���������� ������������
			else if (map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].passable == true)
			{
				// ���� ������������
				moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].passable == false)
			{
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// ���� ��������
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = 0;
			}
		}
		// ���� ����������� �� ��������� � ����� �� ����� ������ � �������
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->platform_turret.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->platform_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
		}
		// ���� ����� ��� �� ����� ���� � ���� ����������
		else if (turretCanShootHero == false && gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate != 0)
		{
			// ���� ������������
			moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
		}
	}

	else if (type == TURRET_HUNTER)
	{
		// ���� � �����(������) ���������� ������������ � �� ���������� ���� � ������ ����� ��������
		if (map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// ������(�����) �������� ����
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->hunter_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfHunterTurret.coordinates.yCoordinate = gameInfo->hunter_turret.coordinates.yCoordinate;
			// ������(�����) �������� �������� ����
			list::addBegin(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		}
		// ���� ���� ���������� � �������� �����������
		else if (gameInfo->bulletOfHunterTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// ���� ���������� ���� � ����� ���������
			if ((gameInfo->bulletOfHunterTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfHunterTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
				 // ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// ���� ��������
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = 0;
			}
			// ���� ������(�����) �� ���� ���������� ������������
			else if (map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].passable == true)
			{
				// ���� ������������
				moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].passable == false)
			{
				// ��������� �������� ����
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// ���� ��������
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = 0;
			}
		}
		// ���� ����������� �� ��������� � ����� �� ����� ������ � �������
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->hunter_turret.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->hunter_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
		}
		// ���� ����� ��� �� ����� ���� � ���� ����������
		else if (turretCanShootHero == false && gameInfo->bulletOfHunterTurret.coordinates.xCoordinate != 0)
		{
			// ���� ������������
			moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
		}
	}
}

// ������� �������� �� ����������� ���� �� �����
void game::moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	if (type == BULLET_OF_STATIONARY_TURRET)
	{
		// �����(������) �������� �������� ����
		list::addBegin(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].types, BULLET_OF_STATIONARY_TURRET);
		// ������������ �������� ���������
		list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		// ���������� �� Ox �������������(�����������) �� step(�� ����)
		gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step;
	}

	else if (type == BULLET_OF_PLATFORM_TURRET)
	{	
		// �����(������) �������� �������� ����
		list::addBegin(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].types, BULLET_OF_PLATFORM_TURRET);
		// ������������ �������� ���������
		list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		// ���������� �� Ox �������������(�����������) �� step(�� ����)
		gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step;
	}

	else if (type == BULLET_OF_HUNTER_TURRET)
	{
		// �����(������) �������� �������� ����
		list::addBegin(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].types, BULLET_OF_HUNTER_TURRET);
		// ������������ �������� ���������
		list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		// ���������� �� Ox �������������(�����������) �� step(�� ����)
		gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step;
	}
}

// ������� �������� �� ����������� ������������� ������
void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// sideOfMoving - ���������� ��� �������� ����������� ������������ � ������� ������ ����
	int sideOfMoving = step;
	// ���� ������ �� ����� �������� ��� ���� ����� � ������ �� ������ ������
	if (turretCanShootHero == false ||
		gameInfo->hero.coordinates.yCoordinate != gameInfo->platform_turret.coordinates.yCoordinate)
	{
		// ���� ������ ���������� ������������ � ������ ��������� ������
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ����� ���������� ������������ � ������ ��������� �����
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate - 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ������ ������������ ������������
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + 1].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ����� ������������ ������������
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate - 1].passable == false)
		{
			sideOfMoving = 1;
			gameInfo->platform_turret.isMovingRight = true;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
	}
}

// ������� �������� �� ����������� ������-��������
void game::turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// ���� ������ �� ����� ��������
	if (turretCanShootHero == false)
	{
		// ���� ����� ������ ������ �� ������ ������ ����� � ������ �� ������ ���������� ������������
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ����� ������ �� ������ ������ ����� � ����� �� ������ ���������� ������������
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ������ ������ �� ������ ������ ����� � ������ �� ������ ������������ ������������
		else if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// ������ �������
			jump(TURRET_HUNTER, gameInfo, map);
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ����� ������ �� ������ ������ ����� � ����� �� ������ ������������ ������������
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// ������ �������
			jump(TURRET_HUNTER, gameInfo, map);
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}