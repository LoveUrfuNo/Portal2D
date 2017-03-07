#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct Hero
	{
		//char type = HERO;
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
	};

	struct Aim
	{
		//char type = AIM_DOT;
		int xCoordinate;
		int yCoordinate;
	};

	struct RedPortal
	{
		//char type = RED_PORTAL;
		int xCoordinate;
		int yCoordinate;
	};

	struct BluePotal
	{
		//char type = BLUE_PORTAL;
		int xCoordinate;
		int yCoordinate;
	};

	struct MapCell					// ��������� MapCell ������ ����� ������ � ������ �����
	{
		char type;					// ���������� ��� �������� �������� (���������, ������ � ��)
		int xCoordinate;			// ���������� �� x ?(��� ���������� � �������)?
		int yCoordinate;			// ���������� �� y ???
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
		//int healthPoints = 100;		// �������� ����������
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapCell** createMap(char* levelName, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal);
}
