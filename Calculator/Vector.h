#pragma once
class Vector
{
public:
	Vector();
	~Vector();
	Vector(Vector& vec);
	Vector(int d, int * elem);
	void Add(const Vector vec);
	void Minus(const Vector vec);
	void print();
	double getCosAngle(Vector &vec);//求取向量夹角的余弦值
private:
	int * _Elem;
	int dimension;//维数
};

