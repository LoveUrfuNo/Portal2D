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
	void jump(GameInfo* gameInfo, game::MapCell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(MapCell** map, GameInfo* gameInfo);
	
	// ������� ��� ����������� �������� �����-������-�����-����

	void moveLeft(char type, GameInfo* gameInfo, MapCell** map);
	void moveRight(char type, GameInfo* gameInfo, MapCell** map);
	void moveUp(char type, GameInfo* gameInfo, MapCell** map);
	void moveDown(char type, GameInfo* gameInfo, MapCell** map);

	// ��������� ������� ��� ������� ������� ������
	void levelOne(); 

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapCell** map, GameInfo* gameInfo);

	void setPortal(char type, GameInfo* gameInfo, game::MapCell** map);
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);

	void activateTheButton(GameInfo* gameInfo, game::MapCell** map);
}