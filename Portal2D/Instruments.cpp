#include "Instruments.h"
#include "Gameplay.h"
#include "Menu.h"

void game::drawFrame(game::MapCell** map, game::GameInfo* gameInfo)		// ��������� �����, ������� ��������� � �������� �������� ��������� ������ ��������
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j].types->value)			// ���������� ������ ��� �������� �������� ������� (��������, ���� � ��)
			{
			case HERO:						// ���� �������� ��� "�����", �� �������������� �����
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, HERO);
				break;

			case BLOCK:						// ���� �������� ��� "����", �� �������������� ����
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, BLOCK);
				break;

			case EMPTY_SPACE:				// ���� �������� ��� "_", �� �������������� ������ ������������
				game::printSpecialSymbol(consoleHandler, i, j, Black, EMPTY_SPACE);
				break;

			case AIM_DOT:					// ���� �������� ��� "������_�����", �� �������������� ������
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, AIM);
				break;

			case BLACK_WALL:				// ���� �������� ��� "������������ �����", �� �������������� ������������ �����
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BLACK_WALL);
				break;

			case EXIT:					// ���� �������� ��� "�����", �� �������������� �����
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, EXIT);
				break;

			case RED_PORTAL:			// ���� �������� ��� "������� ������", �� �������������� ������� ������
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, RED_PORTAL);
				break;

			case BLUE_PORTAL:			// ���� �������� ��� "����� ������", �� �������������� ����� ������ 
				game::printSpecialSymbol(consoleHandler, i, j, LightBlue, BLUE_PORTAL);
				break;

			case BUTTON:
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BUTTON);
				break;

			case TURRET:
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, TURRET);
				break;

			case BULLET:
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, BULLET);
				break;

			case TURRET_EASY:
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, TURRET_EASY);
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "HP: " << gameInfo->hero.healthPoints << "\t\t\tTIME: " << gameInfo->hero.time;
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

void game::freeMemory(game::MapCell** map, game::GameInfo* gameInfo)
{
	delete gameInfo;
	
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		delete map[i];
	}
	
	delete map;
}

void game::printSpecialSymbol(HANDLE consoleHandler, int yCoordinate, int xCoordinate, int color, char symbol)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(consoleHandler, &cursorInfo);
	COORD coordinates;
	coordinates.X = xCoordinate;
	coordinates.Y = yCoordinate;
	SetConsoleCursorPosition(consoleHandler, coordinates);
	SetConsoleTextAttribute(consoleHandler, color);

	cout << symbol;
}

double game::computeTheScore(GameInfo* gameInfo)
{
	double score = 1000 / gameInfo->hero.time;
	return score;
}

void game::showInstruction()
{
	char currentSymbol;
	ifstream fout("Instruction.txt", std::ios_base::in);
	while (!fout.eof())
	{
		currentSymbol = fout.get();

		switch (currentSymbol)
		{
		case HERO_SYMBOL:
			cout << HERO;
			break;

		case AIM_DOT:
			std::cout << AIM;
			break;

		case BLACK_WALL_S:
			std::cout << BLACK_WALL;
			break;

		case EXIT_S:
			std::cout << EXIT;
			break;

		case RED_PORTAL:
			cout << RED_PORTAL;
			break;

		case BUTTON_S:
			cout << BUTTON;
			break;

		default:
			cout << currentSymbol;
			break;
		}

	}
	fout.close();

	cout << endl << " PRESS ANY KEY TO CONTINUE" << endl;
	_getch();
}