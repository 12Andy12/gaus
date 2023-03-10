#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Ratinal.h"
#include "basis.h"
#include <cassert>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;
//abobaboba  

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //получаем наше окно, в котором нужно изменить цвет

bool operator!= (Rational f, int s)
{
	double c = double(double(f.a) / double(f.b));
	//cout << "a/b = " << c << "   s = " << s;
	if (c != s)
		return true;
	return false;
}

bool operator== (Rational f, int s)
{
	double c = double(double(f.a) / double(f.b));
	if (c == s)
		return true;
	return false;
}

bool operator< (Rational f, int s)
{
	double c = double(double(f.a) / double(f.b));
	if (c < s)
		return true;
	return false;
}

bool operator> (Rational f, int s)
{
	double c = double(double(f.a) / double(f.b));
	if (c > s)
		return true;
	return false;
}

bool operator>= (Rational f, Rational s)
{
	double c1 = double(double(f.a) / double(f.b));
	double c2 = double(double(s.a) / double(s.b));
	if (c1 >= c2)
		return true;
	return false;
}

bool operator> (Rational f, Rational s)
{
	double c1 = double(double(f.a) / double(f.b));
	double c2 = double(double(s.a) / double(s.b));
	if (c1 > c2)
		return true;
	return false;
}

ostream& operator<< (ostream& out, Rational s)
{
	if (s.b == 1 || s.a == 0)
		return out << s.a;
	return out << s.a << "/" << s.b;
}

ostream& operator<< (ostream& out, basis b)
{
	for (auto i : b.perm)
		out << i << " ";
	out << "\n";
	return out;
}

istream& operator>> (istream& out, Rational& s)
{
	double number;
	out >> number;
	std::stringstream ss;
	ss << std::setprecision(15) << number;
	std::string strNum = ss.str();
	size_t pos = strNum.find('.');
	int len = 0;
	s.b = 1;
	if (pos != strNum.npos)
	{
		len = strNum.size() - 1 - pos;
		s.a = number;

		for (int i = 0; i < len; ++i)
		{
			s.a *= 10;
			s.b *= 10;
		}
		//cout << " (" << s.a << " " << s.b<<") ";
	}
	else
	{
		s.a = number;
		//cout << " (" << s.a << " " << s.b << ") ";
	}
	return out;
}


int size;
vector<string> vars;
int whitespace = 0;

template<class T>
void read(vector<vector <T> >& matrix, string fileName)
{
	ifstream file;
	file.open(fileName);
	string str;
	vector<T> m;
	getline(file, str);
	whitespace = 0;
	string s = "";
	for (int i = 0; i <= str.size(); i++) {
		if (str[i] == ' ' || i == str.size())
		{
			whitespace++;
			vars.push_back(s);
			s = "";
		}
		else
		{
			s += str[i];
		}

	}
	for (int i = 0; true; i++)
	{
		vector<T> newLine;
		for (int j = 0; j < whitespace + 1; j++)
		{
			T a;

			file >> a;
			newLine.push_back(a);
			if (file.eof())
				break;

		}

		matrix.push_back(newLine);
		if (file.eof())
			break;

	}
}

template<class T>
void printMatrix(vector<vector <T> > matrix)
{
	cout << "\n";
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
			cout << matrix[i][j] << " ";
		cout << '\n';
	}
	cout << "\n";
}

template<class T>
void composition(vector<T>& i, vector<T>& j, T k) //  i = j *k +i
{
	for (int d = 0; d < i.size(); d++) {
		T c = j[d] * k;
		//cout << "||  " << i[d] << " + " << c << "  ||";
		i[d] = i[d] + c;


	}
}

template<class T>
bool divStr(vector<T>& d, T k)
{
	if (k == 0) {
		SetConsoleTextAttribute(h, 4);
		cout << "Нет решения!";
		return false;
	}
	for (int i = 0; i < d.size(); i++) {
		d[i] = d[i] / k;
		//cout << "| " << d[i] << " |";
	}

	return true;
}

template<class T>
bool  solve(vector<vector<T>>& a)
{
	int size = min(a.size(), whitespace);
	for (int k = 0; k < size; k++)
	{

		Rational m(0, 1);
		int id = -1;
		for (int j = k; j < a.size(); ++j)
		{
			//cout<<"\n-"<<j<<"-\n";
			if (rabs(a[j][k]) > m)
			{
				//cout << "\n" << rabs(a[j][k]) << " > " << m << "\n";
				m = rabs(a[j][k]);
				id = j;

			}
			else
			{

				//cout << "\n" << rabs(a[j][k]) << " < " << m << "\n";
			}
			//cout << "\n-\n";
		}
		//cout << "\n--\n";
		if (id != k && id != -1)
			swap(a[id], a[k]);
		int step = 0;
		//cout << "\n--\n";
		if (a[k][k] == 0)
		{
			bool flag = false;
			while (flag == false)
			{
				m.a = -1;
				m.b = 1;
				id = -1;

				for (int i = k; i < size; i++)
				{
					//cout << " i = " << i;
					if (a[i][k + step] != 0 && rabs(a[i][k + step]) > m)
					{
						m = rabs(a[i][k + step]);
						id = i;
					}
				}
				if (id != -1)
				{
					flag = true;
					//cout << "*";
					swap(a[id], a[k]);
					//cout << "*";
					break;
				}
				//cout << "\n( " << k << " " << step << ")\n";
				if (k + step >= whitespace - 1 && a[k][k + step + 1] != 0)
				{
					SetConsoleTextAttribute(h, 4);
					cout << "Нет решений\n";
					return false;
				}
				//cout << "\n-\n";
				if (k + step == whitespace - 1 && a[k][k + step + 1] == 0)
				{
					//cout << "\n--\n";
					a.erase(a.begin() + k);
					size = min(a.size(), whitespace);
					//cout << "\n---\n";
					break;
				}
				//cout << "\n----\n";
				if (flag == false)
				{
					step++;
				}

			}


		}
		if (k >= size)
			break;
		if (a[k][k + step] != 1)
		{
			if (divStr(a[k], a[k][k + step]) == false)
				return false;
		}
		/*else
			cout << a[k][k] << " != 1";*/


		//printMatrix(a);
		for (int i = k - 1; i >= 0; i--)
			composition(a[i], a[k], a[i][k + step] * -1);

		for (int i = k + 1; i < a.size(); i++)
			composition(a[i], a[k], a[i][k + step] * -1);

		//printMatrix(a);
	}

	cout << "\n";

	return true;
}

bool isCorrect = false;



vector<vector <Rational> > mainGaus()
{
	vector<vector <Rational> > matrix;
	string fileName;
	cin >> fileName;

	read(matrix, fileName + ".txt");
	printMatrix(matrix);
	//solve(matrix);

	if (solve(matrix) == true)
	{
		printMatrix(matrix);
		SetConsoleTextAttribute(h, 3);
		for (int i = 0; i < vars.size(); ++i)
		{
			int line = -1;
			for (int j = 0; j < matrix.size(); ++j)
			{
				if (matrix[j][i] == 1)
				{
					line = j;
					break;
				}
			}

			if (line == -1)
				continue;

			cout << vars[i] << " = " << matrix[line][matrix[line].size() - 1];
			for (int j = matrix[line].size() - 2; j >= 0; --j)
			{
				if (j == i)
					continue;
				if (matrix[line][j] != 0)
				{

					if (matrix[line][j] < 0)
						cout << " + ";
					else
						cout << " - ";
					cout << matrix[line][j] << vars[j];
				}

			}
			cout << "\n";

		}
		isCorrect = true;
	}
	else
		printMatrix(matrix);

	for (int i =0;i<matrix.size();++i)
	{
		bool isZeroline = true;
		for (auto j : matrix[i])
		{
			if (j != 0)
				isZeroline = false;
		}
		if (isZeroline == true)
			matrix.erase(matrix.begin() + i);
	}

	return matrix;
}
void sort(vector<int>& vec1, vector<int>& vec2) {
	for (int i = 0; i < vec1.size() - 1; i++) {
		int min = vec1[i], min_index = i;
		for (int j = i + 1; j < vec1.size(); j++) {
			if (vec1[j] < min) {
				min = vec1[j];
				min_index = j;
			}
		}
		if (i != min_index) {
			swap(vec1[i], vec1[min_index]);
			swap(vec2[i], vec2[min_index]);
		}
	}
}

bool isBasisCorrect = true;

vector<Rational> finaly(vector<vector <Rational> >& matrix, int size, basis& bas)
{
	isBasisCorrect = true;
	vector<int> counter(matrix[0].size(), 0);
	vector<Rational> res(size, 0);
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[0].size(); ++j)
		{
			if (matrix[i][j] != 0)
				counter[j] += 1;
		}
	}
	sort(counter, bas.perm);

	for (int j = 0; j < bas.perm.size(); ++j)
	{
		bool isOne = false;
		for (int i = 0; i < matrix.size(); ++i)
		{
			if (matrix[i][j] != 0)
			{
				res[bas.perm[j]] = matrix[i].back();
				matrix.erase(matrix.begin() + i);
				isOne = true;
				break;
			}
				
		}
		if (isOne == false)
		{
			isBasisCorrect = false;
		}
	}
	return res;
}

int main()
{

	setlocale(0, "");
	SetConsoleTextAttribute(h, 2);
	vector<vector <Rational> > matrix;
	matrix = mainGaus();
	if (isCorrect == false)
	{
		SetConsoleTextAttribute(h, 15);
		return 0;
	}


	SetConsoleTextAttribute(h, 6);
	basis permutation(matrix[0].size() - 1, matrix.size());
	do {
		cout << "Столбцы предполагаемого базиса\n";
		cout << permutation;
		vector<vector <Rational> > newMatrix(matrix.size(), vector<Rational>(permutation.perm.size()));
		for (int i = 0; i < newMatrix.size(); ++i)
		{
			for (int j = 0; j < permutation.perm.size(); ++j)
				newMatrix[i][j] = matrix[i][permutation.perm[j]];
			newMatrix[i].push_back(matrix[i].back());
		}
		whitespace = permutation.perm.size();
		printMatrix(newMatrix);

		if (solve(newMatrix) == false)
		{
			SetConsoleTextAttribute(h, 4);
			cout << "Нет базиса!\n";
			SetConsoleTextAttribute(h, 6);
			continue;

		}
		//printMatrix(newMatrix);
		vector<Rational> res = finaly(newMatrix, matrix[0].size(), permutation);
		if (isBasisCorrect)
		{
			cout << "(";
			for (int i=0;i<res.size()-1;++i)
				cout << res[i] << ", ";
			cout << res.back() << ");\n";
		}
		else
		{
			SetConsoleTextAttribute(h, 4);
			cout << "Нет базиса!\n";
			SetConsoleTextAttribute(h, 6);
		}


	} while (permutation.next());

	SetConsoleTextAttribute(h, 15);
}
