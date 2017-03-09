#pragma once

#include "Definitions.h"
#include "Instruments.h"
#include "Stack.h"

namespace game
{
	struct GameInfo
	{
		struct Hero							// ������ ������ � ����� (����������, ���� ��������)
		{
			int xCoordinate;
			int yCoordinate;
			int healthPoints = 100;
		} hero;

		struct Objects                  // ������ ������ �� �������� �� ����� (������, �������)
		{
			int xCoordinate = 0;
			int yCoordinate = 0;
		} redPortal, bluePortal, aim, blackWall, exitFromLevel, button;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		Stack<char>* types;			// ���������� ��� �������� �������� (���������, ������ � ��)
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
