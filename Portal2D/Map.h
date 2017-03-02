#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct MapShell					// ��������� MapShell ������ ����� ������ �� �������� ������� ��������
	{
		char type;					// ���������� ��� �������� �������� (���������, ������ � ��)
		int xCoordinate;			// ���������� �� x ?(��� ���������� � �������)?
		int yCoordinate;			// ���������� �� y ???
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
		int healthPoints = 100;		// �������� ����������
	};

	// ������� ����������� ����� �� ����� � ��������� ������ ��������, ������� ��������� � �������� �������� ��� ������
	MapShell** createMap(char* levelName);
}
