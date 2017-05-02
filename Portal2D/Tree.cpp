#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
	/* ������� ������ � ��������� � ����������� �� ��������� "varaint" */
	void createTree(BranchForNumber<records::DataAboutTheChampion> **tree, char *fileName, int variant)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *tree;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);      // ��������� ����� �� ����� ������� �� ����� ����������� 

			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(
				records::initializationDataAboutTheChampion(buf)
			);   // ���������� � ������������� ���������� �� ������

			if (variant == SCORE)     // ���������� �������� � ����������� �� ����� 
			{
				addInTree(*data, add, SCORE); 
			}
			else if (variant == LEVEL)     // ���������� �������� � ����������� �� ������ 
			{
				addInTree(*data, add, LEVEL);
			}
			else if (variant == STRING)
			{
				addInTree(*data, add, STRING);     // ���������� �������� � ����������� �� ����� 
			}
			delete data;
			delete[] buf;
		}
		*tree = add;
		fin.close();
	}

	/* ��������� ������� � ������ */
	void addInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&tree, int variant)
	{
		if (!tree)       // ���� ������ ������ ��� ����� �����, �� ������� ������� � �������������� ����� ��������� 
		{
			tree = new tree::BranchForNumber<records::DataAboutTheChampion>;
			tree->data = newData;
		}
		else 
		{
			if (variant == SCORE)        // ���� ������������� �� �����
			{
				if (tree->data.score > newData.score)
				{
					tree::addInTree(newData, tree->left, SCORE);
				}
				else
				{
					tree::addInTree(newData, tree->right, SCORE);
				}
			}
			else if (variant == LEVEL)        // ���� ������������� �� ������
			{
				if (tree->data.level > newData.level)
				{
					tree::addInTree(newData, tree->left, LEVEL);
				}
				else
				{
					tree::addInTree(newData, tree->right, LEVEL);
				}
			}
			else if (variant == STRING)        // ���� ������������� �� �����
			{
				int size1 = tree->data.name.length() + 1, size2 = newData.name.length() + 1;
				char *str1 = new char[size1], *str2 = new char[size2];
				strcpy_s(str1, size1, tree->data.name.c_str());
				strcpy_s(str2, size2, newData.name.c_str());

				if (strcmp(str1, str2) > 0)
				{
					tree::addInTree(newData, tree->left, STRING);
				}
				else
				{
					tree::addInTree(newData, tree->right, STRING);
				}
				delete[] str1;
				delete[] str2;
			}
		}
	}

	/* ���������� ����������� ������� */
	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->left)
		{
			tree = tree->left;
		}
		return tree->data;
	}

	/* ���������� ������������ ������� */
	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->right)      
		{
			tree = tree->right;
		}
		return tree->data;
	}

	/* ����������� ������ */
	void freeMemory(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		if (tree)     
		{
			tree::freeMemory(tree->left);
			tree::freeMemory(tree->right);
			delete tree;
		}
	}
}
