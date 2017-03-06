#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
	struct MapShell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};

	//void push(char type, MapShell* &next);
	//char pop(MapShell* &next);

	void drawFrame(MapShell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}