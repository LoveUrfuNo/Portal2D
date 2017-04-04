#pragma once

#include "Stack.h"
#include "List.h"

namespace game
{
	struct Hero							// ������ ������ � ����� (����������, ���� ��������)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
		double score = 4000.0;
		double time = 10000.0;
	};

	struct Objects                  // ������ ������ �� �������� �� ����� (������, �������)
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWall, exitFromLevel, button, turret;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		list::List<char>* types;	// ���������� ��� �������� �������� (���������, ������ � ��)
		bool passable = true;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
