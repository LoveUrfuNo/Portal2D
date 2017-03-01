#include "Definitions.h"
#include "Map.h"
#include "Instruments.h"

int game::findHeroYCoordinate(game::MapShell** map)		// ������� ���� ���������� ��������� �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)			// ���� ���� � ������ ������������ �����
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return i;	// ����� �������� ������� �����, ������� ���������� Y ����������
		}
	}
}

int game::findHeroXCoordinate(game::MapShell** map)		// ������� ���� ���������� ��������� �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)			// ���� ���� � ������ ������������ �����
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return j;	// ����� �������� ������� �����, ������� ���������� X ����������
		}
	}
}

int game::findAimXCoordinate(game::MapShell** map)		// ������� ���� ���������� ������� �� X � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == AIM_DOT) return j;	// ����� �������� ������� �����, ������� ���������� X ����������
		}
	}
}

int game::findAimYCoordinate(game::MapShell** map)		// ������� ���� ���������� ������� �� Y � ���������� ��, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == AIM_DOT) return i;	// ����� �������� ������� �����, ������� ���������� Y ����������
		}
	}
}


void game::drawFrame(game::MapShell** map)		// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j].type)			// ���������� ������ ��� �������� �������� ������� (��������, ���� � ��)
			{
			case HERO:						// ���� �������� ��� "�����", �� �������������� �����
				std::cout << HERO;
				break;

			case BLOCK:						// ���� �������� ��� "����", �� �������������� ����
				std::cout << BLOCK;
				break;

			case EMPTY_SPACE:				// ���� �������� ��� "_", �� �������������� ������ ������������
				std::cout << EMPTY_SPACE;
				break;

			case AIM_DOT:					// ���� �������� ��� "������_�����", �� �������������� ������
				std::cout << AIM;
				break;
				
			case BLACK_WALL:				// ���� �������� ��� "������������ �����", �� �������������� ������������ �����
				std::cout << BLACK_WALL;
				break;

			case EXIT:					// ���� �������� ��� "�����", �� �������������� �����
				std::cout << EXIT;
				break;

			case RED_PORTAL:
				std::cout << RED_PORTAL;
				break;

			case BLUE_PORTAL:
				std::cout << BLUE_PORTAL;
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}


int game::findPortalXCoordinate(char type, MapShell** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == type) return j;
		}
	}
}

int game::findPortalYCoordinate(char type, MapShell** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == type) return i;
		}
	}
}

void game::clearScreen()		// ������� ������� ������� (��� ��������)
{
	HANDLE Handle = nullptr;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cursor;
	Cursor.X = 0;
	Cursor.Y = 0;
	SetConsoleCursorPosition(Handle, Cursor);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(Handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(Handle, &structCursorInfo);
}
