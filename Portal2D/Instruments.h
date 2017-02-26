#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(Map** map);	// ������� ���� ���������� ��������� �� X � ���������� ��
	int findHeroYCoordinate(Map** map);	// ������� ���� ���������� ��������� �� Y � ���������� ��

	int findAimXCoordinate(Map** map);  // ������� ���� ���������� ������� �� X � ���������� ��
	int findAimYCoordinate(Map** map);	// ������� ���� ���������� ������� �� Y � ���������� ��

	void drawFrame(Map** map);			// ��������� �����
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}