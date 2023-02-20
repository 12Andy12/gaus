#include "basis.h"
basis::basis(int col, int row)
{
	perm.resize(row);
	for (int i = 0; i < row; ++i)
		perm[i] = i;
	this->row = row - 1;
	index = row - 1;
	this->col = col - 1;
}

bool basis::next()
{
	if (perm[row] < col) {
		index = row;
		++perm[index];
		return true;
	}
	else { 
		--index;
		if (index < 0)
			return false;
		++perm[index];
		for (int i = index + 1; i <= row; ++i)
			perm[i] = perm[index] + (i - index);
	}
	return true;
}

int basis::operator[](int id)
{
	if (id <= row && id>=0) 
		return perm[id];
	else 
		throw "Index out of range";
}