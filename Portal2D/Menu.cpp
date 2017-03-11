#include "Menu.h"
#include "Records.h"
#include "Gameplay.h"
#include "Definitions.h"
#include "Queue.h"
#include "List.h"
#include "Tree.h"

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

void Stand(int x, int y, int k, char *str)
{
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = 0;
	ci.dwSize = 100;
	SetConsoleCursorInfo(H, &ci);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(H, c);
	SetConsoleTextAttribute(H, k);

	if (str == "Level 1" && k == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(1);
	}
	else if (str == "Level 2" && k == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(2);
	}
	else if (str == "Level 3" && k == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(3);
	}
	else if (str == "Level 4" && k == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(4);
	}
	else if (str == "Level 5" && k == 10)
	{
		cout << str << " ";
		records::giveBestPlayerInLevel(5);
	}
	else
	{
		cout << str << "\n";
	}
}

void Hat()
{
	const int rowsCount = 5;
	const int columnsCount = 55;
	const unsigned char levelData[rowsCount][columnsCount + 1] =
	{
		"           ***   **** ***  ***  *   *     ***  ***   ",
		"           *  *  *  * *  *  *  * *  *       *  *  *  ",
		"           ***   *  * * *   * * * * *     * *  *  *  ",
		"           *     *  * *  *  * *   * *     *    *  *  ",
		"           *     **** *  *  * *   * ***   ***  ***   ",

	};
	cout << "\t";
	for (int r = 0; r < rowsCount; r++)
	{
		for (int c = 0; c < columnsCount; c++)
		{
			cout << levelData[r][c];
		}
		cout << "\n\t";
	}
}

void Point()
{
	Hat();
	Stand(30, 9, GREEN_COLOR, "Start game");
	Stand(30, 11, GREEN_COLOR_DARK, "Records");
	Stand(30, 13, GREEN_COLOR_DARK, "Exit");
}

/***
 * kjhfvjhgcdjgfdcg
 */
void Point2()
{
	Hat();
	Stand(30, 9, GREEN_COLOR, "Random level");
	Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
	Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
	Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
	Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
	Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
	Stand(30, 21, GREEN_COLOR_DARK, "Back");
}

void Point3()
{
	Hat();
	Stand(30, 9, GREEN_COLOR, "Show all records");
	Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
	Stand(30, 13, GREEN_COLOR_DARK, "Back");
}

void RewriterCaseDownPoint(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Start game");
		Stand(30, 11, GREEN_COLOR, "Records");
		break;
	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Records");
		Stand(30, 13, GREEN_COLOR, "Exit");
		break;
	}
}

void RewriterCaseDownPoint2(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Random level");
		Stand(30, 11, GREEN_COLOR, "Level 1");
		break;
	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
		Stand(30, 13, GREEN_COLOR, "Level 2");
		break;
	case 4:
		Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
		Stand(30, 15, GREEN_COLOR, "Level 3");
		break;
	case 5:
		Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
		Stand(30, 17, GREEN_COLOR, "Level 4");
		break;
	case 6:
		Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
		Stand(30, 19, GREEN_COLOR, "Level 5");
		break;
	case 7:
		Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
		Stand(30, 21, GREEN_COLOR, "Back");
		break;
	}
}

void RewriterCaseDownPoint3(int a)
{
	switch (a)
	{
	case 2:
		Stand(30, 9, GREEN_COLOR_DARK, "Show all records");
		Stand(30, 11, GREEN_COLOR, "Show 10 records");
		break;
	case 3:
		Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
		Stand(30, 13, GREEN_COLOR, "Back");
		break;
	}
}

void RewriterCaseUpPoint(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Start game");
		Stand(30, 11, GREEN_COLOR_DARK, "Records");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Records");
		Stand(30, 13, GREEN_COLOR_DARK, "Exit");
		break;
	case 3:
		Stand(30, 13, GREEN_COLOR, "Exit");
		break;
	}
}

void RewriterCaseUpPoint2(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Random level");
		Stand(30, 11, GREEN_COLOR_DARK, "Level 1");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Level 1");
		Stand(30, 13, GREEN_COLOR_DARK, "Level 2");
		break;
	case 3:
		Stand(30, 13, GREEN_COLOR, "Level 2");
		Stand(30, 15, GREEN_COLOR_DARK, "Level 3");
		break;
	case 4:
		Stand(30, 15, GREEN_COLOR, "Level 3");
		Stand(30, 17, GREEN_COLOR_DARK, "Level 4");
		break;
	case 5:
		Stand(30, 17, GREEN_COLOR, "Level 4");
		Stand(30, 19, GREEN_COLOR_DARK, "Level 5");
		break;
	case 6:
		Stand(30, 19, 10, "Level 5");
		Stand(30, 21, GREEN_COLOR_DARK, "Back");
		break;
	}
}

void RewriterCaseUpPoint3(int a)
{
	switch (a)
	{
	case 1:
		Stand(30, 9, GREEN_COLOR, "Show all records");
		Stand(30, 11, GREEN_COLOR_DARK, "Show 10 records");
		break;
	case 2:
		Stand(30, 11, GREEN_COLOR, "Show 10 records");
		Stand(30, 13, GREEN_COLOR_DARK, "Back");
		break;
	case 3:
		Stand(30, 13, GREEN_COLOR, "Back");
		break;
	}
}

void UserSelection(int Cur)
{
	system("cls");
	switch (Cur)
	{
	case 1:
		Point2();
		MoveToMenuPoint2();
		break;
	case 2:
		Point3();
		MoveToMenuPoint3();
		break;
	case 3:;
		break;
	}
}

void UserSelection2(int Cur)
{
	queue::Queue<int> *begin = new queue::Queue<int>;
	system("cls");
	switch (Cur)
	{
	case 1:
		cout << "Random level";
		std::cout << queue::checkCurrentSizeOfQueue(begin) << std::endl;
		std::cout << queue::generatingRandomLevelNumber(begin);
		std::cout << queue::generatingRandomLevelNumber(begin);
		std::cout << queue::generatingRandomLevelNumber(begin);
		std::cout << queue::generatingRandomLevelNumber(begin) << std::endl;
		std::cout << queue::checkCurrentSizeOfQueue(begin) << std::endl;
		queue::freeMemory(begin);
		break;
	case 2:
		/*cout << "Level 1";*/
		SetConsoleTextAttribute(H, 7);
		game::levelOne();
		break;
	case 3:
		cout << "Level 2";
		break;
	case 4:
		cout << "Level 3";
		break;
	case 5:
		cout << "Level 4";
		break;
	case 6:
		cout << "Level 5";
		break;
	case 7:
		Point();
		MoveToMenuPoint();
		break;
	}
}

void UserSelection3(int Cur)
{
	system("cls");
	tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;
	records::DataAboutTheChampion empty;
	std::ifstream fin(FILE_NAME_RECORDS);
	tree::BranchForNumber<records::DataAboutTheChampion> **s = &tree;
	tree::BranchForNumber<records::DataAboutTheChampion> *search;
	int counter = 0;
	switch (Cur)
	{
	case 1:
		cout << "All Records";
		records::addInRecordsOrShowRecords(empty, "show");
		break;

	case 2:
		cout << "10 Records";
		records::addInRecordsOrShowRecords(empty, "show10");
		system("cls");

		tree::addTree(&tree, FILE_NAME_RECORDS);
		std::cout << "\nmin = " << tree::getMinimum(tree).score << std::endl;
		std::cout << "max = " << tree::getMaximum(tree).score << std::endl;

		search = *s;
		while (search)
		{
			if (counter)
				*s = tree::searchByScore(search->right, 43.23);
			else
				*s = tree::searchByScore(search, 43.23);
			search = *s; 
			if (search)
				std::cout << search->data.name << " -> " << search->data.level << std::endl;
			counter++;
		}
		tree::freeMemory(tree);
		break;

		/*case 3:
			Point();
			MoveToMenuPoint();
			break;*/
	}
}

void MoveToMenuPoint()
{
	bool f = true;
	int position = 1;

	while (f == true)
	{
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position < 3)
				position++;
			RewriterCaseDownPoint(position);
			break;

		case UP_ARROW:
			if (position > 1)
				position--;
			RewriterCaseUpPoint(position);
			break;

		case ENTER:
			UserSelection(position);
			f = false;
			break;
		}
	}
}

void MoveToMenuPoint2()
{
	bool f = true;
	int position = 1;

	while (f == true)
	{
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position < 7)
				position++;
			RewriterCaseDownPoint2(position);
			break;

		case UP_ARROW:
			if (position > 1)
				position--;
			RewriterCaseUpPoint2(position);
			break;

		case ENTER:
			UserSelection2(position);
			f = false;
			break;
		}
	}
}

void MoveToMenuPoint3()
{
	bool f = true;
	int position = 1;

	while (f == true)
	{
		int code = _getch();
		switch (code)
		{
		case DOWN_ARROW:
			if (position < 3)
				position++;
			RewriterCaseDownPoint3(position);
			break;

		case UP_ARROW:
			if (position > 1)
				position--;
			RewriterCaseUpPoint3(position);
			break;

		case ENTER:
			UserSelection3(position);
			f = false;
			break;
		}
	}
}
