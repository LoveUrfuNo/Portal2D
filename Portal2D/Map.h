#pragma once

#include "Definitions.h"
#include "Instruments.h"

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

		struct Coordinates                  // ������ ������ �� �������� �� ����� (������, �������)
		{
			int xCoordinate;
			int yCoordinate;
		} redPortal, bluePortal, aim;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		char type;					// ���������� ��� �������� �������� (���������, ������ � ��)
		//int xCoordinate;			// ���������� �� x ?(��� ���������� � �������)?
		//int yCoordinate;			// ���������� �� y ???
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
