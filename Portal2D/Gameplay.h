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
	void jump(Hero* hero, game::MapCell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(MapCell** map, Hero* hero, Object* aim, Object* redPortal, Object* bluePortal);
	
	// ������� ��� ����������� �������� �����-������-�����-����

	template <class T>
	void moveLeft(char type, T *object, MapCell** map);

	template <class T>
	void moveRight(char type, T *object, MapCell** map);

	template <class T>
	void moveUp(char type, T *object, game::MapCell** map);

	template <class T>
	void moveDown(char type, T *object, game::MapCell** map);

	// ��������� ������� ��� ������� ������� ������
	void levelOne(); 

	// �������� ����������� ��������, ��������� ����������
	template <class T>
	void gravity(MapCell** map, T* object);

	template <class T>
	void setPortal(char type, T* object, Object* aim, game::MapCell** map);
	/*void enterThePortal(char type, MapCell** map);*/
}