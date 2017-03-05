#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	// �������� ����������� ��������, ��������� ������, ���� �� ��������
	void jump(Hero* hero, game::MapShell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(MapShell** map, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal);
	
	// ������� ��� ����������� �������� �����-������-�����-����

	template <class T>
	void moveLeft(char type, T *object, MapShell** map);
	template <class T>
	void moveRight(char type, T *object, MapShell** map);
	template <class T>
	void moveUp(char type, T *object, game::MapShell** map);
	template <class T>
	void moveDown(char type, T *object, game::MapShell** map);
	

	// ��������� ������� ��� ������� ������� ������
	void levelOne(); 

	// �������� ����������� ��������, ��������� ����������
	template <class T>
	void gravity(MapShell** map, T* object);

	template <class T>
	void setPortal(char type, T* object, Aim* aim, game::MapShell** map);
	/*void enterThePortal(char type, MapShell** map);*/
}