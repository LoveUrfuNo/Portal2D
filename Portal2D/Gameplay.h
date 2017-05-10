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
	/* ������������� ������� ���� � ���������� ���-�� �����������, ����������� �� �����*/
	double pause(GameInfo* gameInfo, MapCell** map);

	// �������� ����������� ��������, ��������� ������, ���� �� ��������
	void jump(char type, GameInfo* gameInfo, MapCell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(GameInfo* gameInfo, MapCell** map);

	// ������� ��� ����������� �������� �����-������-�����-����
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, game::MapCell** map);
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, game::MapCell** map);

	// ��������� ������� ��� ������� ������� ������
	records::DataAboutTheChampion* startLevel(char* levelName);

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapCell** map, GameInfo* gameInfo);

	// �������� ��������� �������
	void setPortal(char type, GameInfo* gameInfo, MapCell** map);

	// �������� �������� �� ��������
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);	

	// ������� ��������� ������
	void activateTheButton(GameInfo* gameInfo, MapCell** map);

	// ������� ����������� ������� � �����
	void replayceTheAimToHero(GameInfo* gameInfo, MapCell** map);

	// ������� ���������, �� ������� �� �������, ���������� � ����� ���� (����� �� ����� �����, ��������� �� � ������ ��������)
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning);
	
	// ������� ������ �� ������
	bool quitTheLevel(GameInfo* gameInfo, MapCell** map);

	bool objectIsStandingOnTheFloor(Coordinates coordinates, MapCell** map);

	bool movingPossableOx(Coordinates coordinates, GameInfo* gameInfo, MapCell** map, int sideOfMovingOx, char type);

	bool movingPossableOy(Coordinates coordinates, GameInfo* gameInfo, MapCell** map, int sideOfMovingOx, char type);

	bool oneCellAboveTheObjectIsFree(Coordinates coordinates, MapCell** map);

	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map);

	Coordinates getCoordinates(GameInfo* gameInfo, char type);

	void setOXCoordinates(GameInfo* gameInfo, char type);

	void setOYCoordinates(GameInfo* gameInfo, char type);

	void changeOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx);

	void changeOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy);
}