#pragma once

#include "targetver.h"

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include "time.h"


void runMainOperations();
void printArray(int* arr, int sizeArr, bool toResult);
void printArray(int* arr, int sizeArr);
bool checkValue(int val);
void prepareArray1(int* arr, int size);
int getZeroCount(int* arr, int size);
void prepareArray3(int* arr, int &size);
void prepareArray4(int* arr, int &size);
void init();
void insert(int* arr, int index, int elem, int &sizeArr);
void remove(int* arr, int index, int &sizeArr);
int generateValue();
int getMaxMinItemIndex(int* arr, int sizeArr, bool needMax);
void sortArray(int* arr, int sizeArr, bool asc);
void show(char* chars);
void show(int num);
void readArray(std::string filename, int* arr, int arrSize);