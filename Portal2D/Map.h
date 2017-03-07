#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct Hero							// ������ ������ � ����� (����������, ���� ��������)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
	};

	struct Object                  // ������ ������ �� �������� �� ����� (������, �������)
	{
		int xCoordinate;
		int yCoordinate;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		char type;					// ���������� ��� �������� �������� (���������, ������ � ��)
		//int xCoordinate;			// ���������� �� x ?(��� ���������� � �������)?
		//int yCoordinate;			// ���������� �� y ???
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, Hero* hero, Object* aim, Object* redPortal, Object* bluePortal);
}
