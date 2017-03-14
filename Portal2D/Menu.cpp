﻿#include "Menu.h"
#include "Tree.h"
#include "Menu.h"
#include "Tree.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

void menu::drawLogo()
{
	cout << "\t\t\t\t***   **** ***  ***  *   *     ***  ***   " << endl;
	cout << "\t\t\t\t*  *  *  * *  *  *  * *  *       *  *  *  " << endl;
	cout << "\t\t\t\t***   *  * * *   * * * * *     * *  *  *  " << endl;
	cout << "\t\t\t\t*     *  * *  *  * *   * *     *    *  *  " << endl;
	cout << "\t\t\t\t*     **** *  *  * *   * ***   ***  ***   " << endl;
	cout << "\n\n\n";
}

void menu::printPointRecord(int key)
{
	drawLogo();																			// ������ ����

	/* � ����������� �� ����, �� ����� ������ ����������� ������������,
	������ ����*/
	switch (key)
	{
	case Search:
		cout << "\t\t\t\t\t<<     Search         >>" << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case ShowAllRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t<<  Show All Records  >>" << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case Show10Records:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t<<  Show 10 Records   >>" << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case BackRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t<<     Back           >>" << endl;
		break;
	}
}

void menu::printMenu(int key)
{
	drawLogo();																			// ������ ����

	/* � ����������� �� ����, �� ����� ������ ����������� ������������,
	������ ����*/
	switch (key)
	{
	case Start:
		cout << "\t\t\t\t\t<<  Start  >>" << endl;
		cout << "\t\t\t\t\t   Records   " << endl;
		cout << "\t\t\t\t\t    Exit     " << endl;
		break;
	case Records:
		cout << "\t\t\t\t\t    Start    " << endl;
		cout << "\t\t\t\t\t<< Records >>" << endl;
		cout << "\t\t\t\t\t    Exit     " << endl;
		break;
	case Exit:
		cout << "\t\t\t\t\t    Start    " << endl;
		cout << "\t\t\t\t\t   Records   " << endl;
		cout << "\t\t\t\t\t<<  Exit   >>" << endl;
		break;
	}
}

void menu::printPointStart(int key)
{
	//game::clearScreen();
	system("cls");
	drawLogo();																			// ������ ����

	/*� ����������� �� ����, �� ����� ������ ����������� ������������,
		������ ����*/
	switch (key)
	{
	case Instruction:
		cout << "\t\t\t\t\t<<  Instruction  >>" << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case RandomLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t<<  Random Level >>" << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case Level1:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t<<    Level 1    >>"; records::giveBestPlayerInLevel(1);
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case Level2:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t<<    Level 2    >>"; records::giveBestPlayerInLevel(2);
		cout << "\t\t\t\t\t      Back         " << endl;
		break;

	case BackLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t<<    Back       >>" << endl;
		break;
	}

}

void menu::doPointRecords()
{
	int key = Search;																	// ����� �� ������� ����������� ������������

	/*������� ������� ����� Search, ������ ����� BackRecords,
	����� ������� ��������� ���� ������������ printPointRecord*/
	ParametersForMenu parametersForMenu = { Search, BackRecords, &printPointRecord };	

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
		system("cls");

		/*������� � ������ ������� ������ ������������*/
		switch (key)
		{

		case Search:
			break;

		case ShowAllRecords:
			break;

		case Show10Records:
			break;

		default:
			break;
		}
	} while (key != BackRecords);

	system("cls");
}

void menu::doPointStart()
{
	int key = Instruction;																// ����� �� ������� ����������� ������������

	/*������� ������� ����� Instruction, ������ ����� BackLevel,
	����� ������� ��������� ���� ������������ printPointStart*/
	ParametersForMenu parametersForMenu = { Instruction, BackLevel, &printPointStart };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
		system("cls");

		/*������� � ������ ������� ������ ������������*/
		switch (key)
		{

		case Instruction:
			game::showInstruction();
			break;

		case RandomLevel:
			system("pause");
			break;

		case Level1:
			game::startLevel("Lvl_1.txt");
			break;

		case Level2:
			system("pause");
			break;

		default:
			break;
		}
	} while (key != BackLevel);

	system("cls");
}

<<<<<<< HEAD
int menu::controlMenu(ParametersForMenu borders)
=======
//��������� ���������� ���� � ��� ����� �� �����
int menu::controlMenu(ParametersForMenu parametersForMenu)
>>>>>>> 1da2863863ecd120dfcaebc3a5fa0f3936d461b9
{
	int key = parametersForMenu.upBorder;													// key ����� ������ �������� ������ ����
	int press;																				// ������� ������������
	game::clearScreen();
	parametersForMenu.print(key);															// ������� ������ ������� ����
	press = _getch();																		// ��������� �������� ������� �������

	/*���� ������ ���������, �� ��������� �����*/
	if (press == ARROWS)
	{
		/*���� �� ����� Enter ������������ �� ����*/
		while (press != ENTER)
		{
			press = _getch();																// ������� �������� ���������

			/*���� ������ ��������� ����, �� ���������� �� ����� ����
			  ���� ������ ��������� �����, �� ����������� �� ����� �����*/
			switch (press)
			{
			case UP_ARROW:

				/*���� ������������ �� ������ �������� ������ ����,
				�� ����������� �� ����� ����*/
				if (key != parametersForMenu.upBorder)
					key -= 1;
				break;

			case DOWN_ARROW:

				/*���� ������������ �� ������ ������� ������ ����,
					�� ���������� �� ����� ����*/
				if (key != parametersForMenu.lowerBorder)
					key += 1;
				break;
			}
			game::clearScreen();
			parametersForMenu.print(key);													// ������� ������ ������� ����
		}
	}
	game::clearScreen();
	return key;																				// ���������� ����� ������������
}

void menu::menu()
{
	int key;
	/*������� ������� ����� Start, ������ ����� Exit,
	����� ������� ��������� ���� ������������ printMenu*/
	ParametersForMenu borders = { Start, Exit, &printMenu };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(borders);															// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter

		/*Ïîñëå íàæàòèÿ êíîïêè Enter, çàõîäèì â ïóíêò êîòîðûé áûë âûáðàí*/
		switch (key)
		{
		case Start:
			doPointStart();
			break;

		case Records:
			doPointRecords();
			break;

		default:
			break;
		}
	} while (key != Exit);
}
