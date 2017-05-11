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
		shootHero(STATIONARY_TURRET, BULLET_OF_STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootHero, step);
		shootHero(PLATFORM_TURRET, BULLET_OF_PLATFORM_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootHero, step);
		shootHero(TURRET_HUNTER, BULLET_OF_HUNTER_TURRET, gameInfo, map, turretCanShootHero, step);
	}
}

// ���������� ����������� �������� �������� (���� � �������), ����������� �� ��������� �����
int game::determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map)
{
	int direction = NO_STEP;
	if (getCoordinates(gameInfo, HERO).xCoordinate > getCoordinates(gameInfo, type).xCoordinate)
	{
		direction = STEP_RIGHT_OR_DOWN;
	}
	else if (getCoordinates(gameInfo, HERO).xCoordinate < getCoordinates(gameInfo, type).xCoordinate)
	{
		direction = STEP_LEFT_OR_UP;
	}
	return direction;
}

// ���������, ������ �� ������ ��������
bool game::checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	bool turretCanShoot = false;
	bool wallIsHere = false;
	int searcher = getCoordinates(gameInfo, type).xCoordinate;
	if (step != NO_STEP &&
		getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, type).yCoordinate)
	{
		while (getCoordinates(gameInfo, HERO).xCoordinate != searcher && wallIsHere == false)
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value == HERO)
			{
				wallIsHere = false;
				// � ����������� ������ ����������� ���
				searcher = searcher + step;
			}
			// ���� �� ����������� ������ ��� �����
			else if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value != BLOCK)
			{
				searcher = searcher + step;
			}
			// ���� �� ����������� ������ ���� �����
			else if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value == BLOCK)
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
	return turretCanShoot;
}

// ������� ���������� ��������� ���� (�� ���������, ������������)
void game::shootHero(char type, char bullet, GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// ���� � �����(������) ���������� ������������ � �� ���������� ���� � ������ ����� ��������
	if (map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + step].passable == true &&
	getCoordinates(gameInfo, bullet).xCoordinate == 0 && turretCanShootHero == true)
	{
		// ������(�����) �������� ����
		setOXCoordinates(gameInfo, bullet, step);
		setOYCoordinates(gameInfo, bullet);
		// ������(�����) �������� �������� ����
		list::addBegin(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
	}

// ���� ���� ���������� � �������� �����������
	else if (getCoordinates(gameInfo, bullet).xCoordinate != 0 && step != NO_STEP)
	{
		// ���� ���������� ���� � ����� ���������
		if ((getCoordinates(gameInfo, bullet).yCoordinate == getCoordinates(gameInfo, HERO).yCoordinate) &&
			(getCoordinates(gameInfo, bullet).xCoordinate == getCoordinates(gameInfo, HERO).xCoordinate))
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // ���������� �������� ������
														   // ��������� �������� ����
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
			// ���� ��������
			setOXCoordinates(gameInfo, bullet, NO_STEP);
		}
		// ���� ������(�����) �� ���� ���������� ������������
		else if (map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].passable == true)
		{
			// ���� ������������
			moveBullet(bullet, gameInfo, map, step);
		}

		else if (map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].passable == false)
		{
			// ��������� �������� ����
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
			// ���� ��������
			setOXCoordinates(gameInfo, bullet, NO_STEP);
		}
	}
// ���� ����������� �� ��������� � ����� �� ����� ������ � �������
	else if (step == NO_STEP && getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, type).yCoordinate)
	{
		gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// � ����� ���������� ��������
	}
// ���� ����� ��� �� ����� ���� � ���� ����������
	else if (turretCanShootHero == false && getCoordinates(gameInfo, bullet).xCoordinate != 0)
	{
		// ���� ������������
		moveBullet(bullet, gameInfo, map, step);
	}
}

// ������� �������� �� ����������� ���� �� �����
void game::moveBullet(char bullet, GameInfo* gameInfo, MapCell** map, int step)
{
	// �����(������) �������� �������� ����
	list::addBegin(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].types, bullet);
	// ������������ �������� ���������
	list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
	// ���������� �� Ox �������������(�����������) �� step(�� ����)
	changeOXCoordinates(gameInfo, bullet, step);
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
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_RIGHT_OR_DOWN].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ����� ���������� ������������ � ������ ��������� �����
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_LEFT_OR_UP].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ������ ������������ ������������
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_RIGHT_OR_DOWN].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// ���� ����� ������������ ������������
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_LEFT_OR_UP].passable == false)
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
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ����� ������ �� ������ ������ ����� � ����� �� ������ ���������� ������������
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ������ ������ �� ������ ������ ����� � ������ �� ������ ������������ ������������
		else if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// ������ �������
			jump(TURRET_HUNTER, gameInfo, map);
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// ���� ����� ����� ������ �� ������ ������ ����� � ����� �� ������ ������������ ������������
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// ������ �������
			jump(TURRET_HUNTER, gameInfo, map);
			// ������ ������������ �� Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}