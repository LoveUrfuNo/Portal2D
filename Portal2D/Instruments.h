#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(MapShell** map);	// ������� ���� ���������� ��������� �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
	int findHeroYCoordinate(MapShell** map);	// ������� ���� ���������� ��������� �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������

	int findAimXCoordinate(MapShell** map);  // ������� ���� ���������� ������� �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
	int findAimYCoordinate(MapShell** map);	// ������� ���� ���������� ������� �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������

	int findPortalXCoordinate(char type, MapShell** map);
	int findPortalYCoordinate(char type, MapShell** map);

	void drawFrame(MapShell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}