#include "Menu.h"
#include "Gameplay.h"
#include "Search.h"
#include "RandomLevel.h"
#include "List.h"

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
		cout << "\t\t\t\t\t<<      Search        >>" << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case ShowAllRecords:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t<<  Show All Records  >>" << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case BestOfTheBest:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t<<  Best Of The Best  >>" << endl;
		cout << "\t\t\t\t\t         Back           " << endl;
		break;

	case BackRecords:
		cout << "\t\t\t\t\t        Search          " << endl;
		cout << "\t\t\t\t\t    Show All Records    " << endl;
		cout << "\t\t\t\t\t    Best Of The Best    " << endl;
		cout << "\t\t\t\t\t<<       Back         >>" << endl;
		break;
	}
}

void menu::printPointSearch(int key)
{
	drawLogo();

	switch (key)
	{
	case ByScore:
		cout << "\t\t\t\t\t<<   Search By Score   >>" << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case ByLevel:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t<<   Search By Level   >>" << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case ByName:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t<<   Search By Name    >>" << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case BySubstring:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t<< Search By Substring >>" << endl;
		cout << "\t\t\t\t\t          Back           " << endl;
		break;

	case BackRecordsSearch:
		cout << "\t\t\t\t\t     Search By Score     " << endl;
		cout << "\t\t\t\t\t     Search By Level     " << endl;
		cout << "\t\t\t\t\t     Search By Name      " << endl;
		cout << "\t\t\t\t\t   Search By Substring   " << endl;
		cout << "\t\t\t\t\t<<        Back         >>" << endl;
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
	std::system("cls");
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
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case RandomLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t<<  Random Level >>" << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level1:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t<<    Level 1    >>"; records::giveBestPlayerInLevel(1);
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level2:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t<<    Level 2    >>"; records::giveBestPlayerInLevel(2);
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level3:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t<<    Level 3    >>"; records::giveBestPlayerInLevel(3);
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level4:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t<<    Level 4    >>"; records::giveBestPlayerInLevel(4);
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case Level5:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t<<    Level 5    >>"; records::giveBestPlayerInLevel(5);
		cout << "\t\t\t\t\t       Back        " << endl;
		break;

	case BackLevel:
		cout << "\t\t\t\t\t    Instruction    " << endl;
		cout << "\t\t\t\t\t    Random Level   " << endl;
		cout << "\t\t\t\t\t      Level 1      " << endl;
		cout << "\t\t\t\t\t      Level 2      " << endl;
		cout << "\t\t\t\t\t      Level 3      " << endl;
		cout << "\t\t\t\t\t      Level 4      " << endl;
		cout << "\t\t\t\t\t      Level 5      " << endl;
		cout << "\t\t\t\t\t<<     Back      >>" << endl;
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

		std::system("cls");

		/*������� � ������ ������� ������ ������������*/
		switch (key)
		{
		case Search:
			menu::doPointRecordSearch();
			break;

		case ShowAllRecords:
			records::addInRecordsOrShowRecords(NULL, "show");
			break;

		case BestOfTheBest:
			std::cout << "\n\n\t\t\t\t\t Best of the best" << std::endl;
			for (int i = NUMBER_OF_LEVELS; i >= 1; i--)
			{
				std::cout << "\n\t\t\t\t" << (11 - i) << " lvl"; records::giveBestPlayerInLevel(i);
			}
			_getch();
			std::system("cls");
			break;

		default:
			break;
		}
	} while (key != BackRecords);
	std::system("cls");
}

//������������� ��������� ������������� ����� � ������� Records->Search
void menu::doPointRecordSearch()
{
	int key = ByScore;																	// ����� �� ������� ����������� ������������

	/*������� ������� ����� Search, ������ ����� BackRecords,
	����� ������� ��������� ���� ������������ printPointRecord*/
	ParametersForMenu parametersForMenu = { ByScore, BackRecordsSearch, &printPointSearch };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
		std::system("cls");

		list::List<records::DataAboutTheChampion> *list = NULL, *printList = NULL;       // ������ � ���������� ������������� 
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;        // ������ �� ����� �������������

		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		char *name = new char[1000];
		bool print = true;

		switch (key)
		{
		case ByScore:
			createTree(&tree, FILE_NAME_RECORDS, ByScore);     // ������� � �������������� ������ �� �����
			std::cout << "\n\n\n\t\t\t\tEnter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = search::searchAllElements<double>(tree, numberOfScore, search::searchByScoreOfOneResult);       // ��������� �� ������ � ���������� ������������� 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case ByLevel:
			createTree(&tree, FILE_NAME_RECORDS, ByLevel);     // ������� � �������������� ������ �� �������
			std::cout << "\n\n\n\t\t\t\tEnter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = search::searchAllElements<int>(tree, numberOfLevel, search::searchByLevelOfOneResult);       // ��������� �� ������ � ���������� ������������� 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case ByName:
			createTree(&tree, FILE_NAME_RECORDS, ByName);     // ������� � �������������� ������ �� ������
			std::cout << "\n\n\n\t\t\t\tEnter the string: ";
			std::cin >> name;
			std::cout << "\n";
			list = search::searchAllElements<char*>(tree, name, search::searchByStringOfOneResult);       // ��������� �� ������ � ���������� ������������� 

			while (list)
			{
				list::addBegin(&printList, list->value);
				list = list->next;
			}
			break;

		case BySubstring:
			std::cout << "\n\n\n\t\t\t\tEnter the substring: ";
			std::cin >> name;
			std::cout << "\n";
			printList = search::searchBySubstringAllResults(list, name);
			break;

		default:
			print = false;
			break;
		}

		if (print)
		{
			search::printFoundChampions(printList, key);
			system("pause");
		}
		list::freeMemory(list);
		tree::freeMemory(tree);
		delete[] name;
		std::system("cls");

	} while (key != BackRecordsSearch);
}

/* ��� RandomLevel */
char* menu::getFileNameFormNumberOfLevel(int numberOfLevel)
{
	char* result;
	switch (numberOfLevel)
	{
	case 1:
		result = "Lvl_1.txt";
		break;

	case 2:
		result = "Lvl_2.txt";
		break;

	case 3:
		result = "Lvl_3.txt";
		break;

	case 4:
		result = "Lvl_4.txt";
		break;

	case 5:
		result = "Lvl_5.txt";
		break;

	default:
		result = "Lvl_4.txt";
		break;
	}

	return result;
}

//������������� ��������� ������������� ����� � ������� Start
void menu::doPointStart(queue::Queue<int> *queue, bool flag)
{
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
		std::system("cls");

		int numberOfLevel = 0;
		char* fileNameForRandomLevel = "";

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

			fileNameForRandomLevel = menu::getFileNameFormNumberOfLevel(numberOfLevel);
			newChampion = game::startLevel(fileNameForRandomLevel);
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level1:
			newChampion = game::startLevel("Lvl_1.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level2:
			newChampion = game::startLevel("Lvl_2.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level3:
			newChampion = game::startLevel("Lvl_3.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level4:
			newChampion = game::startLevel("Lvl_4.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		case Level5:
			newChampion = game::startLevel("Lvl_5.txt");
			if (newChampion->isPlayerPassedLevel == true)
			{
				records::addInRecordsOrShowRecords(newChampion, "add");
			}
			break;

		default:
			break;
		}
	} while (key != BackLevel);

	std::system("cls");
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
	ParametersForMenu parametersForMenu = { Start, Exit, &printMenu };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu);															// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter

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