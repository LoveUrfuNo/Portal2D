#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
	struct MapCell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};

	//void push(char type, MapCell* &next);
	//char pop(MapCell* &next);

<<<<<<< HEAD
	//int findSomeTypeXCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
	//int findSomeTypeYCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������

	void drawFrame(MapShell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
=======
	void drawFrame(MapCell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
>>>>>>> Andrey
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}