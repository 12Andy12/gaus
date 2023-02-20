#include "Ratinal.h"

Rational rabs(Rational a)
{
	Rational r;
	r.a = abs(a.a);
	r.b = abs(a.b);
	return r;
}


Rational Rational::operator- (Rational s)
{
	Rational r;
	r.a = a * s.b - b * s.a;
	r.b = b * s.b;
	long long c = Nod(r.b, r.a);
	r.a = r.a / c;
	r.b = r.b / c;
	return r;
}

Rational Rational::operator+ (Rational s)
{
	Rational r;
	r.a = a * s.b + b * s.a;
	r.b = b * s.b;
	int c = Nod(r.b, r.a);
	r.a = r.a / c;
	r.b = r.b / c;
	return r;
}

Rational Rational::operator/ (Rational s)
{
	Rational r;
	r.a = a * s.b;
	r.b = b * s.a;
	if (r.b == 0)
	{
		cout << "nelzia delit na Zero" << endl;
		exit(1);
	}
	long long c = Nod(r.b, r.a);
	r.a = r.a / c;
	r.b = r.b / c;
	return r;
}
Rational Rational::operator* (int s)
{
	Rational r;
	r.a = a * s;
	r.b = b;
	long long c = Nod(r.b, r.a);
	r.a = r.a / c;
	r.b = r.b / c;
	return r;
}

Rational Rational::operator* (Rational s)
{
	Rational r;
	r.a = a * s.a;
	r.b = b * s.b;
	long long c = Nod(r.b, r.a);
	r.a = r.a / c;
	r.b = r.b / c;
	return r;
}


Rational Rational::operator= (Rational s)
{
	a = s.a;
	if (s.b)
		b = s.b;
	else
	{
		cout << "ne mogu delit na zero" << endl;
		exit(1);
	};
	return *this;
}



long long Rational::Nod(long long a, long long b)
{
	if (a == 0 && b == 0)
		throw "Error"; 
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	if (a % b == 0)
		return b;
	if (b % a == 0)
		return a;
	if (a > b)
		return Nod(abs(a % b), abs(b));
	else
		return Nod(abs(a), abs(b % a));
}
