#include "Vector.h"
#include <iostream>
#include <cmath>
using namespace std;

Vector::Vector()
{
	_Elem = (int*)malloc(100 * sizeof(int));
	dimension = 0;
}

Vector::Vector(int d, int * elem)
{
	_Elem = (int*)malloc(100 * sizeof(int));
	dimension = d;
	for (int i = 0; i < d; i++) {
		_Elem[i] = elem[i];
	}
}

void Vector::Add(const Vector vec)
{
	if (dimension != vec.dimension) exit(0);
	for (int i = 0; i < dimension; i++) {
		_Elem[i] += vec._Elem[i];
	}
}

void Vector::Minus(const Vector vec)
{
	if (dimension != vec.dimension) exit(0);
	for (int i = 0; i < dimension; i++) {
		_Elem[i] -= vec._Elem[i];
	}
}

void Vector::print()
{
	cout << '(';
	for (int i = 0; i < dimension; i++) {
		cout << _Elem[i] << ' ';
	}
	cout << ')' << endl;
}

double Vector::getCosAngle(Vector &vec)
{
	//ÉñÆæ´úÂë£¬Îð¶¯
	double l2 = 0;
	if (dimension != vec.dimension) exit(0);
	for (int i = 0; i < dimension; i++) {
		l2 += (vec._Elem[i]) * (vec._Elem[i]);
	}
	l2 = sqrt(l2);
	double l1 = 0;
	for (int i = 0; i < dimension; i++) {
		l1 += _Elem[i] * _Elem[i];
	}
	l1 = sqrt(l1);
	double x = 0;
	for (int i = 0; i < dimension; i++) {
		x += _Elem[i] * vec._Elem[i];
	}
	return x / (l1 * l2);
}


Vector::~Vector()
{
	if (_Elem != nullptr) delete _Elem;
}

Vector::Vector(Vector & vec)
{
	_Elem = (int*)malloc(100 * sizeof(int));
	dimension = vec.dimension;
	for (int i = 0; i < dimension; i++) {
		_Elem[i] = vec._Elem[i];
	}
}
