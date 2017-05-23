#include "Menu.h"
#include "Gameplay.h"
#include "Search.h"
#include "RandomLevel.h"
#include "Definitions.h"
#include "List.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

// ��������� ��������� ������
void menu::fillArray(string array[], int count, char divider)
{
	ifstream fout("menu.txt");
	string BUF;			// ����� ��� ������ ��������
	
	/*��������� ������ ���� � ������ �������*/
	for (int i = 0; i < count; i++)
	{
		/*������� �������� ������� ��� ������ ������*/
		if (i==0)
			getline(fout, BUF, divider);
		
		getline(fout, array[i]);
	}
	fout.close();
}

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

/*������� ���� �� �����*/
void menu::printMenu(string str[], int points, int key)
{
	drawLogo();

	/*������� �� ����� ������ ������ ������� ����*/
	for (int i = 0; i <= points; i++)
	{
		cout << "\t\t\t\t\t" << str[i];
		if (key == i)
			cout << "   <-";
		cout << endl;
	}
}

//------Control Functions------//
//������������� ��������� ������������� ����� � ������� Records
void menu::doPointRecords()
{
	string pointRecords[START_POINTS];
	fillArray(pointRecords, START_POINTS, '%');

	int key = Search;																	// ����� �� ������� ����������� ������������

	/*������� ������� ����� Search, ������ ����� BackRecords,
	����� ������� ��������� ���� ������������ printPointRecord*/
	ParametersForMenu parametersForMenu = { Search, BackRecords};

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu, pointRecords);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter

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
				std::cout << "\n\t\t\t\t" << (6 - i) << " lvl"; records::printBestPlayerInLevel(i);
			}

			system("pause");
			/*cin.ignore();
			cin.get();
			cin.ignore();*/
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
	string pointRecordSearch[SEARCH_RECORDS_POINTS];
	fillArray(pointRecordSearch, SEARCH_RECORDS_POINTS, '-');

	int key = ByScore;																	// ����� �� ������� ����������� ������������

	/*������� ������� ����� Search, ������ ����� BackRecords,
	����� ������� ��������� ���� ������������ printPointRecord*/
	ParametersForMenu parametersForMenu = {ByScore, BackRecordsSearch};

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu, pointRecordSearch);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
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
		}

		system("pause");
		/*
		cin.ignore();
		cin.get();
		cin.ignore();*/
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
	string pointStart[START_POINTS];
	fillArray(pointStart, START_POINTS, '*');
	int key = Instruction;																// ����� �� ������� ����������� ������������
	records::DataAboutTheChampion *newChampion = NULL;

	/*������� ������� ����� Instruction, ������ ����� BackLevel,
	����� ������� ��������� ���� ������������ printPointStart*/
	ParametersForMenu parametersForMenu = { Instruction, BackLevel, };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{

		key = controlMenu(parametersForMenu, pointStart);											// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter
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
int menu::controlMenu(ParametersForMenu parametersForMenu, string points[])
{
	int key = parametersForMenu.upBorder;													// key ����� ������ �������� ������ ����
	int countOfPoints = parametersForMenu.lowerBorder;
	int press;																				// ������� ������������
	system("cls");
	printMenu(points, countOfPoints, key);															// ������� ������ ������� ����
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

			case ESCAPE:
				press = ENTER;
				key = parametersForMenu.lowerBorder;
				break;
			}
			game::clearScreen();
			system("cls");
			printMenu(points, countOfPoints, key);														// ������� ������ ������� ����
		}
	}
	else if (press == ESCAPE)
		key = parametersForMenu.lowerBorder;

	return key;																				// ���������� ����� ������������
}

//������������� ��������� ������������� ����� � ������� ����
void menu::doMenu(queue::Queue<int> *queue, bool flag)
{
	string mainPoint[MAIN_POINTS];
	fillArray(mainPoint, MAIN_POINTS, '$');

	int key;
	/*������� ������� ����� Start, ������ ����� Exit,
	����� ������� ��������� ���� ������������ printMenu*/
	ParametersForMenu parametersForMenu = { Start, Exit };

	/*���� ������������ �� ������� ����� �� ����� ��������� ����,
	�������������� ����������� �� ����*/
	do
	{
		key = controlMenu(parametersForMenu, mainPoint);															// key �������� �������� ������ �� ������� ����������� ������������ � ����� Enter

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

void menu::menu()
{
	queue::Queue<int> *queue = new queue::Queue<int>;
	menu::doMenu(queue, false);
	if (queue->head)
	{
		queue::freeMemory(queue);
	}
}