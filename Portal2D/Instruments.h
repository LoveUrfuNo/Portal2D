#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

// �� ������ ��������: ��������� ���� � ��������� ������
namespace game
{
	// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void drawFrame(MapCell** map, GameInfo* gameInfo);

	// ������� ������� ������� (��� ��������)
	void clearScreen();
	
	// ��������� ������
	void freeMemory(MapCell** map, GameInfo* gameInfo);
	
	// ����� ������������ ������� � �������� ����� �����
	void printSpecialSymbol(HANDLE consoleHandler, int yCoordinate, int xCoordinate, int color, char symbol);
	
	// ���������� �����, ��������� �������
	double computeTheScore(GameInfo* gameInfo);
	
	// ����� ���������� � ����
	void showInstruction();
}

