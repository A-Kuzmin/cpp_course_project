#include "stdafx.h"

using namespace std;

const int
array1Size = 10,
array2Size = 10,
array3Size = 10,
array4Size = 10,

rangeMinValue = 0,
rangetMaxValue = 5;
const bool includeBoundary = true;

int main()
{
	init();
	bool needExit = false;
	int command;
	do {
		showMenu();
		cin >> command;
		
		switch (command) {
			case 0: 
				needExit = true;
				break;
			case 1:
				prepareArray1();
				break;
			case 2:
				prepareArray2();
				break;
			case 3:
				prepareArray3();
				break;
			case 4:
				prepareArray4();
				break;
		    default:
			    break;
		}
		if (!needExit) {
			needExit = endComand();
		}
	} while (!needExit);
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



void prepareArray3()
{
	int* arr = new int[array3Size * 2];
	int size = array3Size;

	for (int i = 0; i < size; i++)
		arr[i] = generateValue();

	cout << "Массив 3 исходный массив:\n";
	printArray(arr, size);

	int maxValue = arr[getMaxMinItemIndex(arr, size, true)];

	for (int i = 0; i < size; i++) {
		if (arr[i] == 0) {
			i++;
			insert(arr, i, maxValue, size);
		}
	}
	cout << "Массив 3 результат:\n";
	printArray(arr, size);

	cout << "Массив 3 сортированный результат:\n";
	sortArray(arr, size, true);
	printArray(arr, size);
}

void prepareArray4()
{
	int* arr = new int[array4Size * 2];
	int size = array4Size;
	int el;


	cout << "Введите массив:\n";
	for (int i = 0; i < size; i++) {
		cin >> el;
		if (checkValue(el)) {
			arr[i] = el;
		}
		else {
			cout << "Не корректное число " << el << "\n";
			i--;
		}
	}

	cout << "Массив 4 исходный массив:\n";
	printArray(arr, size);

	int from = getMaxMinItemIndex(arr, array1Size, true);
	int to = getMaxMinItemIndex(arr, array1Size, false);

	if (from > to) {
		int temp = to;
		to = from;
		from = temp;
	}
	
	for (int index = to - 1; index > from; index--) {
		remove(arr, index, size);
	}

	cout << "Массив 4 результат:\n";
	printArray(arr, size);
}

void init()
{
    setlocale(LC_ALL, "RUSSIAN");
    srand(unsigned(time(0)));
}

void showMenu()
{
    cout << "Введите команду:\n";
    cout << "1: Массив 1.\n";
    cout << "2: Массив 2.\n";
    cout << "3: Массив 3.\n";
    cout << "4: Массив 4.\n";

    cout << "0: Выйти\n";
}
bool endComand()
{
    int command;
    cout << "Введите команду:\n";
    cout << "0 для выхода\n";
    cout << "любую другую цифру для вывода меню\n";
    cin >> command;
    return command == 0;
}


void insert(int* arr, int index, int elem, int &sizeArr)
{
	for (int j = sizeArr - 1; j >= index; j--)
	{
		arr[j + 1] = arr[j];
	}
	arr[index] = elem;
	sizeArr++;
}

void remove(int* arr, int index, int &sizeArr)
{
	sizeArr--;
	for (int i = index; i < sizeArr; i++)
	{
		arr[i] = arr[i + 1];
	}
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
	if (in.is_open()) {
		try
		{
			int i = 0;
			while (!in.eof() && (i < arrSize)) {
				in >> temp;

				if (checkValue(temp)) {
					arr[i] = temp;
					i++;
				} else {
					throw new exception("Не корректное число в файле.");
				}

			}
            for (; i < arrSize; i++) {
                arr[i] = 0;
            }
		} catch (const std::exception& ex) {
			in.close();
			throw ex;
		}
		in.close();
	} else {
		throw new exception("Файл не найден");
	}
}