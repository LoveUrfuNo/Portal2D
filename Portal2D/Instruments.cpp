#include "Definitions.h"
#include "Map.h"
#include "Instruments.h"

void game::drawFrame(game::MapCell** map)		// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (peek(map[i][j].types))			// ���������� ������ ��� �������� �������� ������� (��������, ���� � ��)
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

			case RED_PORTAL:			// ���� �������� ��� "������� ������", �� �������������� ������� ������
				std::cout << RED_PORTAL;
				break;

			case BLUE_PORTAL:			// ���� �������� ��� "����� ������", �� �������������� ����� ������
				std::cout << BLUE_PORTAL;
				break;

			case BUTTON:
				std::cout << BUTTON;
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

//void game::push(char type, MapCell* &topElement)
//{
//	MapCell* newType = new MapCell;
//	newType->type = type;
//	newType->next = topElement;
//	topElement = newType;
//}
//
//char game::pop(MapCell* &topElement)
//{
//	char temp = topElement->type;
//	MapCell* currentElement = topElement;
//	topElement = topElement->next;
//	delete currentElement;
//	return temp;
//}