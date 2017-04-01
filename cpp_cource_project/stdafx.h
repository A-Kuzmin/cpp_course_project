#pragma once

#include "targetver.h"

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include "time.h"


void printArray(int* arr, int sizeArr);
bool checkValue(int val);
void prepareArray1();
void prepareArray2();
void prepareArray3();
void prepareArray4();
void init();
void insert(int* arr, int index, int elem, int &sizeArr);
void remove(int* arr, int index, int &sizeArr);
int generateValue();
int getMaxMinItemIndex(int* arr, int sizeArr, bool needMax);
void sortArray(int* arr, int sizeArr, bool asc);
void showMenu();
bool endComand();
void readArray(std::string filename, int* arr, int arrSize);