#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "Definitions.h"

namespace game
{
<<<<<<< HEAD
	struct MapShell;

	struct StackOfTypes
	{
		char type;
		StackOfTypes* next;
	};
=======
	int findHeroXCoordinate(Map** map);	// ������� ���� ���������� ��������� �� X � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
	int findHeroYCoordinate(Map** map);	// ������� ���� ���������� ��������� �� Y � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������

	int findAimXCoordinate(Map** map);  // ������� ���� ���������� ������� �� X � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
	int findAimYCoordinate(Map** map);	// ������� ���� ���������� ������� �� Y � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
>>>>>>> Andrey

	//void push(char type, MapShell* &next);
	//char pop(MapShell* &next);

	int findSomeTypeXCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
	int findSomeTypeYCoordinate(char type, MapShell** map);	// ������� ���� ���������� "�������_��_�����" �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������

	void drawFrame(MapShell** map);			// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
	void clearScreen();					// ������� ������� ������� (��� ��������) !(���� �����������)!
}