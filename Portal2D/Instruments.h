#pragma once

#include <iostream>
#include <iomanip>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"
#include "Gameplay.h"

namespace game
{
	struct GameInfo;
	struct MapCell;

	void drawFrame(MapCell** map, GameInfo* gameInfo);	// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();									// ������� ������� ������� (��� ��������) !(���� �����������)!
	void freeMemory(MapCell** map, GameInfo* gameInfo);
	void printSpecialSymbol(HANDLE consoleHandler, int yCoordinate, int xCoordinate, int color, char symbol);
	double computeTheScore(GameInfo* gameInfo);
	void showInstruction();
}

