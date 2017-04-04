#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <conio.h>

#include "Definitions.h"
#include "Structures.h"
#include "Map.h"
#include "Stack.h"

namespace game
{
	struct GameInfo;
	struct MapCell;

	// �������� ����������� ��������, ��������� ������, ���� �� ��������
	void jump(char type, GameInfo* gameInfo, MapCell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(GameInfo* gameInfo, MapCell** map);
	
	// ������� ��� ����������� �������� �����-������-�����-����
	void moveLeft(char type, GameInfo* gameInfo, MapCell** map);
	void moveRight(char type, GameInfo* gameInfo, MapCell** map);
	void moveUp(GameInfo* gameInfo, MapCell** map);
	void moveDown(char type, GameInfo* gameInfo, MapCell** map);

	// ������� ������������ ������, ��� ��������� �������
	void replaceTheAim(GameInfo* gameInfo, MapCell** map);
	//void replaceTheAimMovement(GameInfo* gameInfo, MapCell** map);

	// ��������� ������� ��� ������� ������� ������
	records::DataAboutTheChampion* startLevel(char* levelName); 

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapCell** map, GameInfo* gameInfo);


	void setPortal(char type, GameInfo* gameInfo, MapCell** map);	// �������� ��������� �������
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);	// �������� �������� �� ��������

	void activateTheButton(GameInfo* gameInfo, MapCell** map);	// ������� ��������� ������

	void turretAI(GameInfo* gameInfo, MapCell** map);

	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map);
}