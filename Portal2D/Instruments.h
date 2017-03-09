#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	struct MapCell;

	void drawFrame(MapCell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}