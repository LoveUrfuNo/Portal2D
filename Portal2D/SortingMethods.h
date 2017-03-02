#pragma once

template<typename T> void bubbleSort(T* arr, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

template<typename T> void insertionSort(T *arr, int length)
{
	int item;           // ������ ����������� ��������, ������ �������
	for (int counter = 1; counter < length; counter++)
	{
		T temp = arr[counter];
		item = counter - 1;
		while (item >= 0 && arr[item] > temp)         // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
		{
			arr[item + 1] = arr[item];
			arr[item] = temp;
			item--;
		}
	}
}

template<typename T> void quickSort(T *arr, int l, int r)
{
	int x = arr[l + (r - l) / 2];        //������ ������������ (l+r)/2, �� �� �������� ������������
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		if (i <= j)
		{
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++; j--;
		}
	}
	if (i < r)
		quickSort(arr, i, r);
	if (l < j)
		quickSort(arr, l, j);
}

template<typename T> void shellSort(T *arr, int n)
{
	int i, j, step;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			T tmp = arr[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < arr[j - step])
					arr[j] = arr[j - step];
				else
					break;
			}
			arr[j] = tmp;
		}
	}
}