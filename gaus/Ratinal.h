#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

#include <sstream>

using namespace std;
class Rational
{

public:
	long long a, b; //a-числитель b-знаменатель//
	Rational(long long chislit = 0, long long znamenat = 1) :a(chislit), b(znamenat)
	{
		a = chislit;
		if (znamenat != 0)
			b = znamenat;
		else
		{
			cout << "Ne mogu podelit na ZERO\n";
			exit(1);
		}
	}
	Rational operator+ (Rational);
	Rational operator- (Rational);
	Rational operator* (Rational);
	Rational operator* (int);
	Rational operator/ (Rational);
	Rational operator= (Rational);

	long long Nod(long long, long long);
};
 
Rational rabs(Rational a);

