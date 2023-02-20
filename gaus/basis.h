#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Ratinal.h"
#include <cassert>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;

class basis
{
public:
	vector<int> perm;
	int col;
	int row;
	int index;
	basis(int n, int k);
	bool next();
	int operator[](int index);
};
 

