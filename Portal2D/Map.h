#pragma once

#include "Stack.h"
#include "List.h"

namespace game
{
	struct Coordinates
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct Hero					// ������ ������ � ����� (����������, ���� ��������)
	{
		Coordinates coordinates;
		int healthPoints = 99;
		double score = 4000.0;
		double time = 10000.0;
		bool isPlayerPassedLevel = true;
	};

	struct Objects				// ������ ������ �� �������� �� ����� (������, �������)
	{
		Coordinates coordinates;
	};

	struct Turret				// ������ ������ � �������
	{
		Coordinates coordinates;
		bool isMovingRight = true;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWallOne, blackWallTwo, blackWallThree, blackWallFour,
			exitFromLevel, buttonOne, buttonTwo, buttonThree, buttonFour,
			bulletOfStationaryTurret, bulletOfPlatformTurret, bulletOfHunterTurret, wall;
		Turret hunter_turret, stationary_turret, platform_turret;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		list::List<char>* types;	// ���������� ��� �������� �������� (���������, ������ � ��)
		bool passable = true;		// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
