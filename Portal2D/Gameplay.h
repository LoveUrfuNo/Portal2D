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
	void jump(int heroYCoordinate, int heroXCoordinate, MapShell** map);

	// ��������� ������������ �������� � ����������� �� ������� ������� �������
	void performAnAction(MapShell** map);
	
	// ������� ��� ����������� �������� �����-������-�����-����
	void moveLeft(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveUp(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveDown(char type, int yCoordinate, int xCoordinate, MapShell** map);
	
	// ������� ��� ����������� ������� ������-�����-�����-����
	/*void moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);*/

	// ��������� ������� ��� ������� ������� ������
	void levelOne(); 

	// �������� ����������� ��������, ��������� ����������
	void gravity(MapShell** map);

	void setPortal(char type, int PortalYCoordinate, int PortalXCoordinate, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void enterThePortal(MapShell** map);
}