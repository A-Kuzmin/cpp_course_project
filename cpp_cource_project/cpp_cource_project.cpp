// cpp_cource_project.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;
void printArray(int* arr, int sizeArr);
bool checkValue(int val);
void readArray(string filename, int* arr, int arrSize);
void prepareArray1();
void prepareArray2();
int getMaxItemIndex(int* arr, int sizeArr);
int getMinItemIndex(int* arr, int sizeArr);
int getMaxMinItemIndex(int* arr, int sizeArr, bool needMax);
void sortArray(int* arr, int sizeArr, bool asc);

const int
array1Size = 10,
array2Size = 10,
array3Size = 10,
array4Size = 10;

const int
rangeMinValue = 0,
rangetMaxValue = 5;

const bool includeBoundary = true;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	prepareArray1();
	prepareArray2();
	system("pause");
    return 0;
}
void prepareArray1()
{
	int* arr = new int[array1Size];
	readArray("file2.txt", arr, array1Size);
	cout << "Массив 1 исходный массив:\n";
	printArray(arr, array1Size);

	int from = getMaxMinItemIndex(arr, array1Size, true);
	int to = getMaxMinItemIndex(arr, array1Size, false);
	
	if (from > to) {
		int temp = to;
		to = from;
		from = temp;
	}

	for (int index = from + 1; index < to; index++)	arr[index] = 0;

	cout << "Массив 1 результат:\n";
	printArray(arr, array1Size);
}


void prepareArray2()
{
	int* arr = new int[array2Size];
	readArray("file2.txt", arr, array2Size);
	cout << "Массив 2 исходный массив:\n";
	printArray(arr, array2Size);

	int count = 0;


	for (int i = 0; i < array2Size; i++)	
		if (arr[i] == 0) count++;

	cout << "Массив 2 результат:\n";
	sortArray(arr, array2Size, false);
	printArray(arr, array2Size);
	cout << "Массив содержит " << count << " нулей.\n";
}

int getMaxItemIndex(int* arr, int sizeArr)
{
	int index = 0;

	for (int i = 1; i < sizeArr; i++)
	{
		if (arr[i] > arr[index])  index = i;
	}
	return index;
}

int getMinItemIndex(int* arr, int sizeArr)
{
	int index = 0;

	for (int i = 1; i < sizeArr; i++)
	{
		if (arr[i] < arr[index])  index = i;
	}
	return index;
}

int getMaxMinItemIndex(int* arr, int sizeArr, bool needMax)
{
	int index = 0;

	for (int i = 1; i < sizeArr; i++)
	{
		if (needMax) {
			if (arr[i] >= arr[index])  index = i;
		} else {
			if (arr[i] < arr[index])  index = i;
		}
	}
	return index;
}

bool checkValue(int val)
{
	if (val < rangeMinValue || (!includeBoundary && val == rangeMinValue)) {
		return false;
	}
	if (val > rangetMaxValue || (!includeBoundary && val == rangetMaxValue)) {
		return false;
	}
	return true;
}

int generateValue()
{
	return rangeMinValue + (rand() % (int)(rangetMaxValue - rangeMinValue + 1));
}

void printArray(int* arr, int sizeArr)
{
	int arrSize = sizeof(arr);
	for (int i = 0; i < sizeArr; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << "\n";
}

void sortArray(int* arr, int sizeArr, bool asc)
{
	int temp;
	for (int i = 0; i < sizeArr - 1; i++) {
		for (int j = 0; j < sizeArr - i - 1; j++) {
			if ((asc && arr[j] > arr[j + 1]) || (!asc && arr[j] < arr[j + 1])) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void readArray(string filename, int* arr, int arrSize)
{
	int temp;

	ifstream in(filename);
	if (in.is_open())
	{
		try
		{
			int i = 0;
			while (!in.eof() && (i < arrSize))
			{
				in >> temp;

				if (checkValue(temp)) {
					arr[i] = temp;
					i++;
				}
				else {
					throw new exception("Не корректное число в файле.");
				}

			}
		}
		catch (const std::exception& ex)
		{
			in.close();
			throw ex;
		}
		in.close();
	}
	else
	{
		throw new exception("Файл не найден");
	}
}