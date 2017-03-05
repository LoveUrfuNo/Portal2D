#include "Definitions.h"
#include "Map.h"
#include "Instruments.h"

<<<<<<< HEAD
int game::findSomeTypeXCoordinate(char type, MapShell** map)
=======
// ������� ���� ���������� ��������� �� Y � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
int game::findHeroYCoordinate(game::Map** map)
>>>>>>> Andrey
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == type) return j;
		}
	}
}

<<<<<<< HEAD
int game::findSomeTypeYCoordinate(char type, MapShell** map)
=======
// ������� ���� ���������� ��������� �� X � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
int game::findHeroXCoordinate(game::Map** map)
>>>>>>> Andrey
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == type) return i;
		}
	}
}

<<<<<<< HEAD
void game::drawFrame(game::MapShell** map)		// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
=======
// ������� ���� ���������� ������� �� X � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
int game::findAimXCoordinate(game::Map** map)
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return j;	// ����� �������� ������� �����, ������� ���������� X ����������
			}
		}
	}
}

// ������� ���� ���������� ������� �� Y � ���������� ��, � �������� ��������� ��������� ��������� ������ ��������
int game::findAimYCoordinate(game::Map** map)
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return i;	// ����� �������� ������� �����, ������� ���������� Y ����������
			}
		}
	}
}

// ��������� �����, � �������� ��������� ��������� ��������� ������ ��������
void game::drawFrame(game::Map** map)
>>>>>>> Andrey
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

//void game::push(char type, MapShell* &topElement)
//{
//	MapShell* newType = new MapShell;
//	newType->type = type;
//	newType->next = topElement;
//	topElement = newType;
//}
//
//char game::pop(MapShell* &topElement)
//{
//	char temp = topElement->type;
//	MapShell* currentElement = topElement;
//	topElement = topElement->next;
//	delete currentElement;
//	return temp;
//}