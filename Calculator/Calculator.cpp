#include "Sequence.h"
#include "List.h"
#include "Vector.h"
#include "Operate.h"
#include "ArithmeticX.h"
#include "Matrix.h"
int main()
{
	while (true) {
		Operate::printMenu();
		int c;
		cin >> c;
		Operate::FunctionBox(c);
		//Operate::test(c);
		system("pause");
		//system("cls");
	}

	//double a[3][100] = { {1,2,3},{4,5,6},{7,8,9} };
	//double b[3][100] = { {1,1,1},{1,1,1},{1,1,1} };
	//double c[3][100] = { {2,3,5,6},{1,1,1,1},{4,2,7,1} };
	//double d[2][100] = { {1,2},{2,1} };
	//Matrix mat1(a, 3, 3);
	//Matrix mat2(b, 3, 3);
	//Matrix mat3(c, 3, 4);
	//Matrix mat4(d, 2, 2);
	//auto mm = mat1.multiply(mat3);
	////mm->print();
	//mat2.CalcEigenvalue();

	//ArithmeticX arix("x+1/x","x");
	//arix.print();
	//arix.ChangeVarName("yy");
	//arix.print();

	system("pause");
}

