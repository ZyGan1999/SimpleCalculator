#include "Operate.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;
//------------------------------------头文件---------------------------------


//--------------------------这里是一些定义的结构体和数据类型---------
//纯C里面定义的布尔类型
typedef enum { False = 0, True = 1 }Bool;
//定义矩阵元素的类型为matrixType
typedef double matrixType;

//此结构体用来表示矩阵，其中row为行，column为列，height为高，array用来存放矩阵元素(用一维来模拟二维/三维)
typedef struct
{
	unsigned  row, column, height;
	matrixType *array; //使用时，必须对*array进行初始化
}_Matrix;

//---------下面是QR分解，求解线性方程所用到的一些函数-----------
/*
matrix为要设置大小并分配内存的矩阵，row、column、height分别为行，列，高。
函数调用成功则则返回true,否则返回false
*/
Bool SetMatrixSize(_Matrix *matrix, const unsigned row, const unsigned column, const unsigned height)
{
	unsigned size = row * column * height * sizeof(matrixType);
	if (size <= 0)
	{
		return False;
	}

	matrix->array = (matrixType*)malloc(size);

	//如果分配内存成功
	if (matrix->array)
	{
		matrix->row = row;
		matrix->column = column;
		matrix->height = height;
		return True;
	}
	else
	{
		matrix->row = matrix->column = matrix->height = 0;
		return False;
	}
}

//设置_Matrix矩阵中的所有元素大小为ele
void SetMatrixEle(_Matrix *matrix, matrixType ele)
{
	unsigned size = matrix->row * matrix->column * matrix->height;
	unsigned i;

	for (i = 0; i < size; ++i)
	{
		matrix->array[i] = ele;
	}
}

//设置_Matrix矩阵中的所有元素大小为0
void SetMatrixZero(_Matrix*matrix)
{
	SetMatrixEle(matrix, 0);
}

//判断矩阵是否为空，若为空则返回1，否则返回0
Bool IsNullMatrix(const _Matrix* matrix)
{
	unsigned size = matrix->row * matrix->column * matrix->column;

	if (size <= 0 || matrix->array == NULL)
	{
		return True;
	}
	return False;
}

//销毁矩阵，即释放为矩阵动态分配的内存,并将矩阵的长宽高置0
void DestroyMatrix(_Matrix *matrix)
{
	if (!IsNullMatrix(matrix))
	{
		free(matrix->array);
		matrix->array = NULL;
	}

	matrix->row = matrix->column = matrix->height = 0;
}

//计算矩阵可容纳元素个数，即return row*column*height
unsigned MatrixCapacity(const _Matrix*matrix)
{
	return matrix->row * matrix->column * matrix->height;
}


//||matrix||_2  求A矩阵的2范数
matrixType MatrixNorm2(const _Matrix *matrix)
{
	unsigned size = matrix->row * matrix->column *matrix->height;
	unsigned i;
	matrixType norm = 0;

	for (i = 0; i < size; ++i)
	{
		norm += (matrix->array[i]) *(matrix->array[i]);
	}

	return (matrixType)sqrt(norm);
}

//matrixB = matrix(:,:,height)即拷贝三维矩阵的某层，若matrix为二维矩阵，需将height设置为0
Bool CopyMatrix(_Matrix* matrixB, _Matrix *matrix, unsigned height)
{
	unsigned size, i;
	_Matrix matrixA;

	//判断height值是否正确
	if (height < 0 || height >= matrix->height)
	{
		printf("ERROR: CopyMatrix() parameter error！\n");
		return False;
	}

	//将matrix(:,:,height) 转换为二维矩阵matrixA
	matrixA.row = matrix->row;
	matrixA.column = matrix->column;
	matrixA.height = 1;
	matrixA.array = matrix->array + height * matrix->row * matrix->column;

	//判断两矩阵指向的内存是否相等
	if (matrixA.array == matrixB->array)
	{
		return True;
	}

	//计算matrixA的容量
	size = MatrixCapacity(&matrixA);
	//判断matrixB的容量与matrixA的容量是否相等
	if (MatrixCapacity(matrixB) != size)
	{
		DestroyMatrix(matrixB);
		SetMatrixSize(matrixB, matrixA.row, matrixA.column, matrixA.height);
	}
	else
	{
		matrixB->row = matrixA.row;
		matrixB->column = matrixA.column;
		matrixB->height = matrixA.height;
	}

	for (i = 0; i < size; ++i)
	{
		matrixB->array[i] = matrixA.array[i];
	}

	return True;
}

//matrixC = matrixA * matrixB
Bool MatrixMulMatrix(_Matrix *matrixC, const _Matrix* matrixA, const _Matrix* matrixB)
{
	size_t row_i, column_i, i;
	size_t indexA, indexB, indexC;
	matrixType temp;
	_Matrix tempC;

	if (IsNullMatrix(matrixA) || IsNullMatrix(matrixB))
	{
		return False;
	}

	if (matrixA->column != matrixB->row)
	{
		return False;
	}

	if (MatrixCapacity(matrixC) != matrixA->row * matrixB->column)
	{
		SetMatrixSize(&tempC, matrixA->row, matrixB->column, 1);
	}
	else
	{
		tempC.array = matrixC->array;
		tempC.row = matrixA->row;
		tempC.column = matrixB->column;
		tempC.height = 1;
	}

	for (row_i = 0; row_i < tempC.row; ++row_i)
	{
		for (column_i = 0; column_i < tempC.column; ++column_i)
		{
			temp = 0;
			for (i = 0; i < matrixA->column; ++i)
			{
				indexA = row_i * matrixA->column + i;
				indexB = i * matrixB->column + column_i;

				temp += matrixA->array[indexA] * matrixB->array[indexB];
			}
			indexC = row_i * tempC.column + column_i;

			tempC.array[indexC] = temp;
		}
	}


	if (tempC.array != matrixC->array)
	{
		DestroyMatrix(matrixC);

		matrixC->array = tempC.array;
	}

	matrixC->row = tempC.row;
	matrixC->column = tempC.column;
	matrixC->height = tempC.height;



	return True;
}

//对vector中所有元素排序，sign= 0 时为升序，其余为降序
void SortVector(_Matrix *vector, int sign)
{
	matrixType mid;
	int midIndex;
	int size = MatrixCapacity(vector);
	int i, j;

	if (0 == sign)
	{
		for (i = 0; i < size; ++i)
		{
			mid = vector->array[i];
			midIndex = i;
			for (j = i + 1; j < size; ++j)
			{
				if (mid > vector->array[j])
				{
					mid = vector->array[j];
					midIndex = j;
				}
			}

			vector->array[midIndex] = vector->array[i];
			vector->array[i] = mid;
		}
	}
	else
	{
		for (i = 0; i < size; ++i)
		{
			mid = vector->array[i];
			midIndex = i;
			for (j = i + 1; j < size; ++j)
			{
				if (mid < vector->array[j])
				{
					mid = vector->array[j];
					midIndex = j;
				}
			}

			vector->array[midIndex] = vector->array[i];
			vector->array[i] = mid;
		}
	}
}

//打印矩阵
void PrintMatrix(const _Matrix *matrix)
{
	size_t row_i, column_i, height_i, index;

	for (height_i = 0; height_i < matrix->height; ++height_i)
	{
		(matrix->height == 1) ? printf("[:,:] = \n") : printf("[%d,:,:] = \n", height_i);

		for (row_i = 0; row_i < matrix->row; ++row_i)
		{
			for (column_i = 0; column_i < matrix->column; ++column_i)
			{
				index = height_i * matrix->row * matrix->column + row_i * matrix->column + column_i;
				printf("%12.4g", matrix->array[index]);
			}
			printf("\n");
		}
	}
}

//----------------------QR分解-------------------------------------------

//将A分解为Q和R
void QR(_Matrix *A, _Matrix *Q, _Matrix *R)
{
	unsigned  i, j, k, m;
	unsigned size;
	const unsigned N = A->row;
	matrixType temp;

	_Matrix a, b;

	//如果A不是一个二维方阵，则提示错误，函数计算结束
	if (A->row != A->column || 1 != A->height)
	{
		printf("ERROE: QR() parameter A is not a square matrix!\n");
		return;
	}

	size = MatrixCapacity(A);
	if (MatrixCapacity(Q) != size)
	{
		DestroyMatrix(Q);
		SetMatrixSize(Q, A->row, A->column, A->height);
		SetMatrixZero(Q);
	}
	else
	{
		Q->row = A->row;
		Q->column = A->column;
		Q->height = A->height;
	}

	if (MatrixCapacity(R) != size)
	{
		DestroyMatrix(R);
		SetMatrixSize(R, A->row, A->column, A->height);
		SetMatrixZero(R);
	}
	else
	{
		R->row = A->row;
		R->column = A->column;
		R->height = A->height;
	}

	SetMatrixSize(&a, N, 1, 1);
	SetMatrixSize(&b, N, 1, 1);

	for (j = 0; j < N; ++j)
	{
		for (i = 0; i < N; ++i)
		{
			a.array[i] = b.array[i] = A->array[i * A->column + j];
		}

		for (k = 0; k < j; ++k)
		{
			R->array[k * R->column + j] = 0;

			for (m = 0; m < N; ++m)
			{
				R->array[k * R->column + j] += a.array[m] * Q->array[m * Q->column + k];
			}

			for (m = 0; m < N; ++m)
			{
				b.array[m] -= R->array[k * R->column + j] * Q->array[m * Q->column + k];
			}
		}

		temp = MatrixNorm2(&b);
		R->array[j * R->column + j] = temp;

		for (i = 0; i < N; ++i)
		{
			Q->array[i * Q->column + j] = b.array[i] / temp;
		}
	}

	DestroyMatrix(&a);
	DestroyMatrix(&b);
}

//----------------------使用特征值计算矩阵特征向量-----------------
//eigenVector为计算结果即矩阵A的特征向量
//eigenValue为矩阵A的所有特征值，
//A为要计算特征向量的矩阵
void Eigenvectors(_Matrix *eigenVector, _Matrix *A, _Matrix *eigenValue)
{
	unsigned i, j, q;
	unsigned count;
	int m;
	const unsigned NUM = A->column;
	matrixType eValue;
	matrixType sum, midSum, mid;
	_Matrix temp;

	SetMatrixSize(&temp, A->row, A->column, A->height);

	for (count = 0; count < NUM; ++count)
	{
		//计算特征值为eValue，求解特征向量时的系数矩阵
		eValue = eigenValue->array[count];
		CopyMatrix(&temp, A, 0);
		for (i = 0; i < temp.column; ++i)
		{
			temp.array[i * temp.column + i] -= eValue;
		}

		//将temp化为阶梯型矩阵
		for (i = 0; i < temp.row - 1; ++i)
		{
			mid = temp.array[i * temp.column + i];
			for (j = i; j < temp.column; ++j)
			{
				temp.array[i * temp.column + j] /= mid;
			}

			for (j = i + 1; j < temp.row; ++j)
			{
				mid = temp.array[j * temp.column + i];
				for (q = i; q < temp.column; ++q)
				{
					temp.array[j * temp.column + q] -= mid * temp.array[i * temp.column + q];
				}
			}
		}
		midSum = eigenVector->array[(eigenVector->row - 1) * eigenVector->column + count] = 1;
		for (m = temp.row - 2; m >= 0; --m)
		{
			sum = 0;
			for (j = m + 1; j < temp.column; ++j)
			{
				sum += temp.array[m * temp.column + j] * eigenVector->array[j * eigenVector->column + count];
			}
			sum = -sum / temp.array[m * temp.column + m];
			midSum += sum * sum;
			eigenVector->array[m * eigenVector->column + count] = sum;
		}

		midSum = sqrt(midSum);
		for (i = 0; i < eigenVector->row; ++i)
		{
			eigenVector->array[i * eigenVector->column + count] /= midSum;
		}
	}
	DestroyMatrix(&temp);
}
int CE()
{
	const unsigned NUM = 50; //最大迭代次数

	unsigned N = 3;
	unsigned k;

	_Matrix A, Q, R, temp;
	_Matrix eValue;

	cout << "请输入矩阵阶数" << endl;
	cin >> N;

	//分配内存
	SetMatrixSize(&A, N, N, 1);
	SetMatrixSize(&Q, A.row, A.column, A.height);
	SetMatrixSize(&R, A.row, A.column, A.height);
	SetMatrixSize(&temp, A.row, A.column, A.height);
	SetMatrixSize(&eValue, A.row, 1, 1);

	//A设置为一个简单矩阵
	//A.array[0] = -1;
	//A.array[1] = 2;
	//A.array[2] = 1;
	//A.array[3] = 2;
	//A.array[4] = 4;
	//A.array[5] = -1;
	//A.array[6] = 1;
	//A.array[7] = 1;
	//A.array[8] = -6;
	cout << "请输入矩阵" << endl;
	for (int i = 0; i < N*N; ++i) {
		cin >> A.array[i];
	}


	//拷贝A矩阵元素至temp
	CopyMatrix(&temp, &A, 0);

	//初始化Q、R所有元素为0
	SetMatrixZero(&Q);
	SetMatrixZero(&R);
	//使用QR分解求矩阵特征值
	for (k = 0; k < NUM; ++k)
	{
		QR(&temp, &Q, &R);
		MatrixMulMatrix(&temp, &R, &Q);
	}
	//获取特征值，将之存储于eValue
	for (k = 0; k < temp.column; ++k)
	{
		eValue.array[k] = temp.array[k * temp.column + k];
	}

	//对特征值按照降序排序
	SortVector(&eValue, 1);

	//根据特征值eValue，原始矩阵求解矩阵特征向量Q
	Eigenvectors(&Q, &A, &eValue);

	//打印特征值
	printf("特征值：");
	PrintMatrix(&eValue);

	//打印特征向量
	printf("特征向量");
	PrintMatrix(&Q);
	DestroyMatrix(&A);
	DestroyMatrix(&R);
	DestroyMatrix(&Q);
	DestroyMatrix(&eValue);
	DestroyMatrix(&temp);

	return 0;
}
Operate::Operate()
{
}


Operate::~Operate()
{
}

void Operate::printMenu()
{
	cout << "1.同维度向量的加法" << endl
		<< "2.同维度向量的减法" << endl
		<< "3.一元多项式的加法" << endl
		<< "4.一元多项式的减法" << endl
		<< "5.向量的夹角余弦值" << endl
		<< "6.求多阶导数" << endl
		<< "7.多项式的乘法" << endl
		<< "8.四则运算表达式求值" << endl
		<< "9.含未知数的表达式求值" << endl
		<< "10.操作自定义函数" << endl
		<< "11.矩阵的加法" << endl
		<< "12.矩阵的减法" << endl
		<< "13.矩阵的乘法" << endl
		<< "14.矩阵的转置" << endl
		<< "15.方阵的行列式求值" << endl
		<< "16.方阵的特征值" << endl
		<< "请选择一个操作" << endl;
}

void Operate::FunctionBox(int c)
{
	switch (c)
	{
	case 1: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入第一个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入第二个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Add(v2);
		cout << "运算结果是: ";
		v1.print();
		break;
	}
	case 2: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入被减向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入减数向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Minus(v2);
		cout << "运算结果是: ";
		v1.print();
		break;
	}
	case 3: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "按指数大小,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "第一个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "按指数大小,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.add(l2);
		s1.Add(s2);
		cout << "链表计算结果是:";
		l1.print();
		cout << "顺序表计算结果是:";
		s1.print();
		break;
	}
	case 4: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "第二个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.minus(l2);
		s1.Minus(s2);
		cout << "链表计算结果是:";
		l1.print();
		cout << "顺序表计算结果是:";
		s1.print();
		break;
	}
	case 5: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "请输入向量的维数:" << endl;
		cin >> dimension;
		cout << "请输入第一个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "请输入第二个向量:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);

		cout << "两向量夹角的余弦值为:" << v1.getCosAngle(v2) << endl;

		break;
	}
	case 6: {
		int d;
		int num;
		List l;
		cout << "请输入原始多项式的项数:" << endl;
		cin >> d;
		for (int i = 0; i < d; i++) {
			double coef;
			int expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l.addNode(ListNode(coef, expn));
		}
		l.print();
		cout << "请输入求导次数:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			l.Derivation();
		}
		cout << "求导结果是:";
		l.print();
		break;
	}
	case 7: {
		int d1, d2;
		List l1, l2, result;
		cout << "第一个多项式有几项:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			int coef, expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l1.addNode(ListNode(coef, expn));
		}
		l1.print();
		cout << "第二个多项式有几项:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			int coef, expn;
			cout << "按指数由高到低顺序,请输入第" << i + 1 << "项(系数 指数):" << endl;
			cin >> coef >> expn;
			l2.addNode(ListNode(coef, expn));
		}
		l2.print();
		l1.multiply(l2, result);
		cout << "计算结果是:";
		result.print();
		break;
	}
	case 8: {
		string exp;
		cout << "请输入四则运算表达式" << endl;
		cin >> exp;
		Arithmetic ari(exp);
		cout << "运算结果是: " << ari.getResult() << endl;
		break;
	}
	case 9: {
		string exp;
		string VarName;
		double Val;
		cout << "请输入变量名" << endl;
		cin >> VarName;
		cout << "请输入表达式" << endl;
		cin >> exp;
		cout << "请输入变量的值" << endl;
		cin >> Val;
		ArithmeticX ariX(exp, VarName);
		auto ari = ariX.Assign(Val);
		cout << "运算结果是: " << ari.getResult() << endl;
		break;
	}
	case 10: {
		cout << "可以开始输入指令了" << endl;
		string instruction = "";
		getline(cin, instruction);
		getline(cin, instruction);
		std::list<Function * > funcs;
		
		while (instruction != "ESC") {
			string insName = instruction.substr(0, 3);
			string input = "";
			try{input = instruction.substr(4, instruction.length() - 4);}
			catch (const exception& e) { ; }
			if (insName == "DEF") {
				auto f = Function::DEF(input,funcs);
				funcs.push_back(f);
			}
			else if (insName == "RUN") {
				string funcName = "";
				string Val_str = "";
				int curPos = 0;
				while (input[curPos] != '(') {
					funcName += input[curPos];
					++curPos;
				}
				++curPos;
				while (input[curPos] != ')') {
					Val_str += input[curPos];
					++curPos;
				}
				double val = Arithmetic::String2Num(Val_str);
				for (auto it = funcs.begin(); it != funcs.end(); ++it) {
					if ((*it)->getName() == funcName) {
						cout << "结果是: ";
						(*it)->RUN(val);
						break;
					}
					if (it == funcs.end()) cout << "没有找到对应函数" << endl;
				}
			}
			else if (insName == "WHO") {
				for (auto i : funcs) {
					//cout << (*i).getName() << ' ';
					i->print();
				}
				//cout << endl;
			}
			else {
				cout << "没有对应指令" << endl;
			}

			getline(cin, instruction);
		}
		break;
	}
	case 11: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "请输入两个矩阵的行、列数" << endl;
		cin >> row >> col;
		cout << "请输入第一个矩阵" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "请输入第二个矩阵" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, row, col);
		mat1.add(mat2);
		cout << "结果是:" << endl;
		mat1.print();
		break;
	}
	case 12: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "请输入两个矩阵的行、列数" << endl;
		cin >> row >> col;
		cout << "请输入第一个矩阵" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "请输入第二个矩阵" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, row, col);
		mat1.minus(mat2);
		cout << "结果是:" << endl;
		mat1.print();
		break;
	}
	case 13: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "请输入第一个矩阵的行、列数" << endl;
		cin >> row >> col;
		cout << "请输入第一个矩阵" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "请输入第二个矩阵" << endl;
		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, col, row);
		auto rtn = mat1.multiply(mat2);
		cout << "结果是:" << endl;
		rtn->print();
		break;
	}
	case 14: {
		int row, col;
		double data[100][100];
		cout << "请输入矩阵的行、列数" << endl;
		cin >> row >> col;
		cout << "请输入矩阵" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> data[i][j];
			}
		}
		Matrix mat(data, row, col);
		cout << "结果是:" << endl;
		mat.Transpose();
		mat.print();
		break;
	}
	case 15: {
		int rc;
		double data[100][100];
		cout << "请输入矩阵的行数" << endl;
		cin >> rc;
		cout << "请输入矩阵" << endl;
		for (int i = 0; i < rc; i++) {
			for (int j = 0; j < rc; j++) {
				cin >> data[i][j];
			}
		}
		Matrix mat(data, rc, rc);
		cout << "结果是:" << endl << mat.CalcDeterminant() << endl;
		break;
	}
	case 16: {
		//int rc;
		//double data[100][100];
		//cout << "请输入矩阵的行数" << endl;
		//cin >> rc;
		//cout << "请输入矩阵" << endl;
		//for (int i = 0; i < rc; i++) {
		//	for (int j = 0; j < rc; j++) {
		//		cin >> data[i][j];
		//	}
		//}
		//Matrix mat(data, rc, rc);
		//cout << "结果是:" << endl;
		////mat.CE();
		//mat.CalcEigenvalue();
		CE();
		break;
	}
	default:
		break;
	}
}

void Operate::test(int c)
{
	int dim = 11;//维数
	int x1[100] = { 2, -45, 32, -245, 0, 3442, 5, 0, 25, 56, -23 };//向量1
	int x2[100] = { 8, 90, 55, -3, 0, 67, 790, 234, 804, 0, -687 };//向量2
	Vector v1(11, x1);
	Vector v2(11, x2);

	List L1, L2;
	L1.add(5, 1000); L1.add(-1, 828); L1.add(7, 7); L1.add(-89, 5); L1.add(-23, 3); L1.add(90, 2); L1.add(-235, 1); L1.add(754, 0);
	L2.add(-34, 643); L2.add(554, 103); L2.add(-7, 7); L2.add(-89, 5); L2.add(243, 4); L2.add(-222, 2); L2.add(1, 0);
	//v1.print(); v2.print(); L1.print(); L2.print();
	switch (c)
	{
	case 1: {
		v1.Add(v2);
		v1.print();
		break;
	}
	case 2: {
		v1.Minus(v2);
		v1.print();
		break;
	}
	case 3: {
		L1.add(L2);
		L1.print();
		break;
	}
	case 4: {
		L1.minus(L2);
		L1.print();
		break;
	}
	case 5: {
		cout << v1.getCosAngle(v2) << endl;
		break;
	}
	case 6: {
		int num;
		cout << "请输入求导次数:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			L1.Derivation();
		}
		L1.print();
		break;
	}
	case 7: {
		List result;
		L1.multiply(L2, result);
		result.print();
		break;
	}
	default:
		break;
	}
}

