#pragma once

#include "DistrOfDefine.h"

namespace game
{
	struct Map						// ��������� Map ������ ����� ������ �� �������� ������� ��������
	{
		char type;					// ���������� ��� �������� �������� (���������, ������ � ��)
		int xCoordinate;			// ���������� �� x ?(��� ���������� � �������)?
		int yCoordinate;			// ���������� �� y ???
		bool passable;				// ���������� ������ � ���� ������ � ����������� ������ ������ ��
		int healthPoints = 100;		// �������� ����������
	};

	Map** createMap(char* levelName);	// ������� ����������� ����� �� ����� � ��������� ������ ��������
}