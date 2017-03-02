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

	int findSomeTypeXCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
	int findSomeTypeYCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������

	void drawFrame(MapShell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}