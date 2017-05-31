#include "stdafx.h"

using namespace std;

const int
ARRAY_1_SIZE = 10,
ARRAY_2_SIZE = 10,
ARRAY_3_SIZE = 10,
ARRAY_4_SIZE = 10,

RANGE_MIN_VALUE = 0,
RANGE_MAX_VALUE = 5;
const bool INCLUDE_BOUNDARY = true;

ofstream resultFile;

int main()
{
    try {
        init();
        runMainOperations();
        resultFile.close();
    }
    catch (exception ex) {
        resultFile.close();
        cout << ex.what();
    }

    system("pause");
    return 0;
}

void runMainOperations()
{

    int* arr1 = new int[ARRAY_1_SIZE];
    int* arr2 = new int[ARRAY_2_SIZE];
    int* arr3 = new int[ARRAY_3_SIZE * 2];
    int* arr4 = new int[ARRAY_4_SIZE * 2];
    int size3 = ARRAY_3_SIZE;
    int size4 = ARRAY_4_SIZE;


    readArray("file1.txt", arr1, ARRAY_1_SIZE);
    readArray("file2.txt", arr2, ARRAY_2_SIZE);

    for (int i = 0; i < size3; i++)
        arr3[i] = generateValue();

    int el;
    cout << "Введите массив:\n";
    for (int i = 0; i < size4; i++) {
        cin >> el;
        if (checkValue(el)) {
            arr4[i] = el;
        }
        else {
            cout << "Не корректное число " << el << "\n";
            i--;
        }
    }

    cout << "\n\n";

    show("Массив 1 исходный массив:\n");
    printArray(arr1, ARRAY_1_SIZE);


    show("Массив 2 исходный массив:\n");
    printArray(arr2, ARRAY_2_SIZE);

    show("Массив 3 исходный массив:\n");
    printArray(arr3, size3);

    show("Массив 4 исходный массив:\n");
    printArray(arr4, size4);

    prepareArray1(arr1, ARRAY_1_SIZE);
    show("Массив 1 итоговый массив:\n");
    printArray(arr1, ARRAY_1_SIZE);

    show("Массив 2 содержит ");
    show(getZeroCount(arr2, ARRAY_2_SIZE));
    show(" нулей.\n");

    prepareArray3(arr3, size3);
    show("Массив 3 результат задания:\n");
    printArray(arr3, size3);


    prepareArray4(arr4, size4);
    show("Массив 4 результат задания:\n");
    printArray(arr4, size4);


    show("Массив 2 сортированный по убывынию \n");

    sortArray(arr2, ARRAY_2_SIZE, false);
    printArray(arr2, ARRAY_2_SIZE);

    show("Массив 3 сортированный по возрастанию \n");
    sortArray(arr3, size3, true);
    printArray(arr3, size3);
}

void prepareArray1(int* arr, int size)
{ 
	int from = getMaxMinItemIndex(arr, size, true);
	int to = getMaxMinItemIndex(arr, size, false);
	
	if (from > to) {
		int temp = to;
		to = from;
		from = temp;
	}
	for (int index = from + 1; index < to; index++)	arr[index] = 0;
}


int getZeroCount(int* arr, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] == 0) count++;
    return count;
}



void prepareArray3(int* arr, int &size)
{
    int maxValue = arr[getMaxMinItemIndex(arr, size, true)];
	for (int i = 0; i < size; i++) {
		if (arr[i] == 0) {
			i++;
			insert(arr, i, maxValue, size);
		}
	}
}

void prepareArray4(int* arr, int &size)
{
	int from = getMaxMinItemIndex(arr, size, true);
	int to = getMaxMinItemIndex(arr, size, false);

	if (from > to) {
		int temp = to;
		to = from;
		from = temp;
	}
	
	for (int index = to - 1; index > from; index--) {
		remove(arr, index, size);
	}
}

void init()
{
    setlocale(LC_ALL, "RUSSIAN");
    srand(unsigned(time(0)));

    resultFile.open("result.txt");
    if (!resultFile.is_open()) {
        throw new exception("file result init error");
    }
    resultFile.clear();
}

void show(char* chars)
{
    cout << chars;
    resultFile << chars;
}
void show(int num)
{
    cout << num;
    resultFile << num;
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
	if (val < RANGE_MIN_VALUE || (!INCLUDE_BOUNDARY && val == RANGE_MIN_VALUE)) {
		return false;
	}
	if (val > RANGE_MAX_VALUE || (!INCLUDE_BOUNDARY && val == RANGE_MAX_VALUE)) {
		return false;
	}
	return true;
}

int generateValue()
{
	return RANGE_MIN_VALUE + (rand() % (int)(RANGE_MAX_VALUE - RANGE_MIN_VALUE + 1));
}

void printArray(int* arr, int sizeArr, bool toResult)
{
	for (int i = 0; i < sizeArr; i++)
	{
        if (toResult) {
            show(arr[i]);
            show("\t");
        }
        else {
            cout << arr[i] << "\t";
        }
	}

    if (toResult) {
        show("\n");
    }
    else {
        cout << "\n";
    }
}
void printArray(int* arr, int sizeArr)
{
    printArray(arr, sizeArr, true);
}

void sortArray(int* arr, int size, bool asc)
{
    for (int idx_i = 0; idx_i < size - 1; idx_i++)
    {
        int cur_idx = idx_i;
        for (int idx_j = idx_i + 1; idx_j < size; idx_j++)
        {
            if ((asc && arr[idx_j] < arr[cur_idx]) || (!asc && arr[idx_j] > arr[cur_idx])) {
                cur_idx = idx_j;
            }
        }

        if (cur_idx != idx_i)
        {
            std::swap(arr[idx_i], arr[cur_idx]);
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
