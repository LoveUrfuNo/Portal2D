#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"
#include "Stack.h"

namespace game
{
	struct GameInfo;
	struct MapCell;

	// �������� ����������� ��������, ��������� ������, ���� �� ��������
	void jump(GameInfo* gameInfo, game::MapCell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(GameInfo* gameInfo, MapCell** map);
	
	// ������� ��� ����������� �������� �����-������-�����-����

	void moveLeft(char type, GameInfo* gameInfo, MapCell** map);
	void moveRight(char type, GameInfo* gameInfo, MapCell** map);
	void moveUp(char type, GameInfo* gameInfo, MapCell** map);
	void moveDown(char type, GameInfo* gameInfo, MapCell** map);
	void replaceTheAim(char type, GameInfo* gameInfo, game::MapCell** map);
	// ��������� ������� ��� ������� ������� ������
	double startLevel(char* levelName); 

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapCell** map, GameInfo* gameInfo);

	void setPortal(char type, GameInfo* gameInfo, game::MapCell** map);
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);

	void activateTheButton(GameInfo* gameInfo, game::MapCell** map);

	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map);
}