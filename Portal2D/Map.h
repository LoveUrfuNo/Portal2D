#pragma once

#include "Definitions.h"
#include "Instruments.h"
#include "Stack.h"

namespace game
{
	struct Hero							// ������ ������ � ����� (����������, ���� ��������)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
		double score = 10000;
	};

	struct Objects                  // ������ ������ �� �������� �� ����� (������, �������)
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWall, exitFromLevel, button;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		Stack<char>* types;			// ���������� ��� �������� �������� (���������, ������ � ��)
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
