#include "Menu.h"
#include "Gameplay.h"
#include "Tree.h"
#include "Search.h"
#include "RandomLevel.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

//------Print Functions------//
//������ �������
void menu::drawLogo()
{
	cout << "\t\t\t\t***   **** ***  ***  *   *     ***  ***   " << endl;
	cout << "\t\t\t\t*  *  *  * *  *  *  * *  *       *  *  *  " << endl;
	cout << "\t\t\t\t***   *  * * *   * * * * *     * *  *  *  " << endl;
	cout << "\t\t\t\t*     *  * *  *  * *   * *     *    *  *  " << endl;
	cout << "\t\t\t\t*     **** *  *  * *   * ***   ***  ***   " << endl;
	cout << "\n\n\n";
}

//������� ������� ����, �� ������� ����������� ������������ � ������ Records
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
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case ShowAllRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t<<  Show All Records  >>" << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case Show10Records:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t<<  Show 10 Records   >>" << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case BestOfTheBest:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t<<  Best Of The Best  >>" << endl;
		cout << "\t\t\t\t\t       Back             " << endl;
		break;

	case BackRecords:
		cout << "\t\t\t\t\t       Search           " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Show 10 Records     " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t<<     Back           >>" << endl;
		break;
	}
}

//������� ������� �������� ����, �� ������� ����������� ������������
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

//������� ������� ����, �� ������� ����������� ������������ � ������ Start
void menu::printPointStart(int key)
{
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

//------Control Functions------//
//������������� ��������� ������������� ����� � ������� Records
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
		char *selectOfPlayer = new char[5];

		/*������� � ������ ������� ������ ������������*/
		switch (key)
		{
		case Search:
			std::cout << "\t\t\t\t 1 - search by score\n\t\t\t\t 2 - search by level\n\t\t\t\t 3 - search by name\n\t\t\t\t 4 - search by substring" << std::endl;
			*selectOfPlayer = _getch();
			search::setSearchParametr<int>(atoi(selectOfPlayer));
			break;

		case ShowAllRecords:
			records::addInRecordsOrShowRecords(NULL, "show");
			break;

		case Show10Records:
			records::addInRecordsOrShowRecords(NULL, "show10");
			break;

		case BestOfTheBest:
			std::cout << "\n\n\t\t\t\t\t Best of the best" << std::endl;
			for (int i = NUMBER_OF_LEVELS; i >= 1; i--)
			{
				std::cout << "\n\t\t\t\t" << (11 - i) << " lvl"; records::giveBestPlayerInLevel(i);
			}
			_getch();
			system("cls");
			break;

		default:
			break;
		}
		delete[] selectOfPlayer;

	} while (key != BackRecords);
	system("cls");
}

//������������� ��������� ������������� ����� � ������� Start
void menu::doPointStart(queue::Queue<int> *queue, bool flag)
{
	//PlaySound("mainMenu.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

	int key = Instruction;																// ����� �� ������� ����������� ������������
	records::DataAboutTheChampion *newChampion = NULL;
	/*������� ������� ����� Instruction, ������ ����� BackLevel,
	����� ������� ��������� ���� ������������ printPointStart*/
	ParametersForMenu parametersForMenu = { Instruction, BackLevel, &printPointStart };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
		system("cls");

		int numberOfLevel = 0;
		/*������� � ������ ������� ������ ������������*/
		switch (key)
		{

		case Instruction:
			game::showInstruction();
			break;

		case RandomLevel:
			if (queue::checkCurrentSizeOfQueue<int>(*queue) <= 2 && flag)
			{
				queue::freeMemory(queue);
				numberOfLevel = random::initializeQueueAndReturnHead(queue);
			}
			else
			{
				flag = true;
				numberOfLevel = random::initializeQueueAndReturnHead(queue);
			}
			newChampion = game::startLevel("Lvl_1.txt");
			records::addInRecordsOrShowRecords(newChampion, "add");
			break;

		case Level1:
			newChampion = game::startLevel("Lvl_1.txt");
			records::addInRecordsOrShowRecords(newChampion, "add");
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

//��������� ���������� ���� � ��� ����� �� �����
int menu::controlMenu(ParametersForMenu parametersForMenu)
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
	return key;																				// ���������� ����� ������������
}

//������������� ��������� ������������� ����� � ������� ����
void menu::menu(queue::Queue<int> *queue, bool flag)
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

		/*����� ������� ������ Enter, ������� � ����� ������� ��� ������*/
		switch (key)
		{
		case Start:
			doPointStart(queue, flag);
			break;

		case Records:
			doPointRecords();
			break;

		default:
			break;
		}
	} while (key != Exit);
}