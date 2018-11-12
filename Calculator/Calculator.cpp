#include "Sequence.h"
#include "List.h"
#include "Vector.h"
#include "Operate.h"
#include "ArithmeticX.h"
#include "Matrix.h"
int main()
{
	//while (true) {
	//	Operate::printMenu();
	//	int c;
	//	cin >> c;
	//	Operate::FunctionBox(c);
	//	//Operate::test(c);
	//	system("pause");
	//	system("cls");
	//}

	int a[3][100] = { {1,2,3},{4,5,6},{7,8,9} };
	int b[3][100] = { {1,1,1},{1,1,1},{1,1,1} };
	int c[4][100] = { {2,3,5,6},{1,1,1,1},{4,2,7,1},{3,2,5,8} };
	int d[2][100] = { {1,2},{2,1} };
	Matrix mat1(a, 3, 3);
	Matrix mat2(b, 3, 3);
	Matrix mat3(c, 4, 4);
	Matrix mat4(d, 2, 2);
	mat1.print();
	mat2.print();
	mat1.add(mat2);
	mat1.print();
	mat1.minus(mat2);
	mat1.print();
	auto mat11 = mat1.getAij(0, 0);
	mat11->print();
	auto mat31 = mat3.getAij(2, 2);
	mat31->print();
	cout << mat1.CalcDeterminant() << endl;
	cout << mat2.CalcDeterminant() << endl;
	mat3.print();
	mat4.print();
	cout << mat3.CalcDeterminant() << endl;
	system("pause");
}

