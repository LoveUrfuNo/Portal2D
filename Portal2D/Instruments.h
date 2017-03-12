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

	void drawFrame(MapCell** map, GameInfo* gameInfo);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}
