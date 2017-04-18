#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	void TurretAI(char type, GameInfo* gameInfo, MapCell** map);
	int determinePositionOfHero(char type, GameInfo* gameInfo, MapCell** map);
	bool checkTurretShotConditions(char type, GameInfo* gameInfo, MapCell** map, int step);
	void shootingToHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
	void moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step);
	void platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);


	//// ������� �������� �� ������ �� ������
	//void turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight);
	//// �������� �� �������������� ��������� �������
	//void turretPatrol(GameInfo* gameInfo, MapCell** map, bool *isMovingRight, bool *wallIsHere);
	//// ������� �������� �� �������� �� �����
	//void shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool *wallIsHere);
	//// �������� �� �������� ������
	//void shootingRight(GameInfo* gameInfo, MapCell** map);
	//// �������� �� �������� �����
	//void shootingLeft(GameInfo* gameInfo, MapCell** map);
	//// ������� ���������, ���� �� ����� ������ � ������� �����
	//bool checkTheWall(GameInfo* gameInfo, MapCell** map);

	//void turretAI(GameInfo* gameInfo, MapCell** map);
	//void turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	//bool spottingHero(GameInfo* gameInfo, MapCell** map);
	//bool spottingHeroPatrol(GameInfo* gameInfo, MapCell** map);
	//void shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
}
