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
	double getCosAngle(Vector &vec);//��ȡ�����нǵ�����ֵ
private:
	int * _Elem;
	int dimension;//ά��
};

