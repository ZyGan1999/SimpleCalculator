#include "Operate.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;
//------------------------------------ͷ�ļ�---------------------------------


//--------------------------������һЩ����Ľṹ�����������---------
//��C���涨��Ĳ�������
typedef enum { False = 0, True = 1 }Bool;
//�������Ԫ�ص�����ΪmatrixType
typedef double matrixType;

//�˽ṹ��������ʾ��������rowΪ�У�columnΪ�У�heightΪ�ߣ�array������ž���Ԫ��(��һά��ģ���ά/��ά)
typedef struct
{
	unsigned  row, column, height;
	matrixType *array; //ʹ��ʱ�������*array���г�ʼ��
}_Matrix;

//---------������QR�ֽ⣬������Է������õ���һЩ����-----------
/*
matrixΪҪ���ô�С�������ڴ�ľ���row��column��height�ֱ�Ϊ�У��У��ߡ�
�������óɹ����򷵻�true,���򷵻�false
*/
Bool SetMatrixSize(_Matrix *matrix, const unsigned row, const unsigned column, const unsigned height)
{
	unsigned size = row * column * height * sizeof(matrixType);
	if (size <= 0)
	{
		return False;
	}

	matrix->array = (matrixType*)malloc(size);

	//��������ڴ�ɹ�
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

//����_Matrix�����е�����Ԫ�ش�СΪele
void SetMatrixEle(_Matrix *matrix, matrixType ele)
{
	unsigned size = matrix->row * matrix->column * matrix->height;
	unsigned i;

	for (i = 0; i < size; ++i)
	{
		matrix->array[i] = ele;
	}
}

//����_Matrix�����е�����Ԫ�ش�СΪ0
void SetMatrixZero(_Matrix*matrix)
{
	SetMatrixEle(matrix, 0);
}

//�жϾ����Ƿ�Ϊ�գ���Ϊ���򷵻�1�����򷵻�0
Bool IsNullMatrix(const _Matrix* matrix)
{
	unsigned size = matrix->row * matrix->column * matrix->column;

	if (size <= 0 || matrix->array == NULL)
	{
		return True;
	}
	return False;
}

//���پ��󣬼��ͷ�Ϊ����̬������ڴ�,��������ĳ������0
void DestroyMatrix(_Matrix *matrix)
{
	if (!IsNullMatrix(matrix))
	{
		free(matrix->array);
		matrix->array = NULL;
	}

	matrix->row = matrix->column = matrix->height = 0;
}

//������������Ԫ�ظ�������return row*column*height
unsigned MatrixCapacity(const _Matrix*matrix)
{
	return matrix->row * matrix->column * matrix->height;
}


//||matrix||_2  ��A�����2����
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

//matrixB = matrix(:,:,height)��������ά�����ĳ�㣬��matrixΪ��ά�����轫height����Ϊ0
Bool CopyMatrix(_Matrix* matrixB, _Matrix *matrix, unsigned height)
{
	unsigned size, i;
	_Matrix matrixA;

	//�ж�heightֵ�Ƿ���ȷ
	if (height < 0 || height >= matrix->height)
	{
		printf("ERROR: CopyMatrix() parameter error��\n");
		return False;
	}

	//��matrix(:,:,height) ת��Ϊ��ά����matrixA
	matrixA.row = matrix->row;
	matrixA.column = matrix->column;
	matrixA.height = 1;
	matrixA.array = matrix->array + height * matrix->row * matrix->column;

	//�ж�������ָ����ڴ��Ƿ����
	if (matrixA.array == matrixB->array)
	{
		return True;
	}

	//����matrixA������
	size = MatrixCapacity(&matrixA);
	//�ж�matrixB��������matrixA�������Ƿ����
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

//��vector������Ԫ������sign= 0 ʱΪ��������Ϊ����
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

//��ӡ����
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

//----------------------QR�ֽ�-------------------------------------------

//��A�ֽ�ΪQ��R
void QR(_Matrix *A, _Matrix *Q, _Matrix *R)
{
	unsigned  i, j, k, m;
	unsigned size;
	const unsigned N = A->row;
	matrixType temp;

	_Matrix a, b;

	//���A����һ����ά��������ʾ���󣬺����������
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

//----------------------ʹ������ֵ���������������-----------------
//eigenVectorΪ������������A����������
//eigenValueΪ����A����������ֵ��
//AΪҪ�������������ľ���
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
		//��������ֵΪeValue�������������ʱ��ϵ������
		eValue = eigenValue->array[count];
		CopyMatrix(&temp, A, 0);
		for (i = 0; i < temp.column; ++i)
		{
			temp.array[i * temp.column + i] -= eValue;
		}

		//��temp��Ϊ�����;���
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
	const unsigned NUM = 50; //����������

	unsigned N = 3;
	unsigned k;

	_Matrix A, Q, R, temp;
	_Matrix eValue;

	cout << "������������" << endl;
	cin >> N;

	//�����ڴ�
	SetMatrixSize(&A, N, N, 1);
	SetMatrixSize(&Q, A.row, A.column, A.height);
	SetMatrixSize(&R, A.row, A.column, A.height);
	SetMatrixSize(&temp, A.row, A.column, A.height);
	SetMatrixSize(&eValue, A.row, 1, 1);

	//A����Ϊһ���򵥾���
	//A.array[0] = -1;
	//A.array[1] = 2;
	//A.array[2] = 1;
	//A.array[3] = 2;
	//A.array[4] = 4;
	//A.array[5] = -1;
	//A.array[6] = 1;
	//A.array[7] = 1;
	//A.array[8] = -6;
	cout << "���������" << endl;
	for (int i = 0; i < N*N; ++i) {
		cin >> A.array[i];
	}


	//����A����Ԫ����temp
	CopyMatrix(&temp, &A, 0);

	//��ʼ��Q��R����Ԫ��Ϊ0
	SetMatrixZero(&Q);
	SetMatrixZero(&R);
	//ʹ��QR�ֽ����������ֵ
	for (k = 0; k < NUM; ++k)
	{
		QR(&temp, &Q, &R);
		MatrixMulMatrix(&temp, &R, &Q);
	}
	//��ȡ����ֵ����֮�洢��eValue
	for (k = 0; k < temp.column; ++k)
	{
		eValue.array[k] = temp.array[k * temp.column + k];
	}

	//������ֵ���ս�������
	SortVector(&eValue, 1);

	//��������ֵeValue��ԭʼ������������������Q
	Eigenvectors(&Q, &A, &eValue);

	//��ӡ����ֵ
	printf("����ֵ��");
	PrintMatrix(&eValue);

	//��ӡ��������
	printf("��������");
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
	cout << "1.ͬά�������ļӷ�" << endl
		<< "2.ͬά�������ļ���" << endl
		<< "3.һԪ����ʽ�ļӷ�" << endl
		<< "4.һԪ����ʽ�ļ���" << endl
		<< "5.�����ļн�����ֵ" << endl
		<< "6.���׵���" << endl
		<< "7.����ʽ�ĳ˷�" << endl
		<< "8.����������ʽ��ֵ" << endl
		<< "9.��δ֪���ı��ʽ��ֵ" << endl
		<< "10.�����Զ��庯��" << endl
		<< "11.����ļӷ�" << endl
		<< "12.����ļ���" << endl
		<< "13.����ĳ˷�" << endl
		<< "14.�����ת��" << endl
		<< "15.���������ʽ��ֵ" << endl
		<< "16.���������ֵ" << endl
		<< "��ѡ��һ������" << endl;
}

void Operate::FunctionBox(int c)
{
	switch (c)
	{
	case 1: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�������һ������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "������ڶ�������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Add(v2);
		cout << "��������: ";
		v1.print();
		break;
	}
	case 2: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�����뱻������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "�������������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);
		v1.Minus(v2);
		cout << "��������: ";
		v1.print();
		break;
	}
	case 3: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "��ָ����С,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "��ָ����С,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.add(l2);
		s1.Add(s2);
		cout << "�����������:";
		l1.print();
		cout << "˳����������:";
		s1.print();
		break;
	}
	case 4: {
		int d1, d2;
		List l1, l2;
		Sequence s1, s2;
		ListNode n1[100], n2[100];
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n1[i]._coef >> n1[i]._expn;
			l1.addNode(n1[i]);
			s1.Insert(1, n1[i]);
		}
		l1.print();
		cout << "�ڶ�������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> n2[i]._coef >> n2[i]._expn;
			l2.addNode(n2[i]);
			s2.Insert(1, n2[i]);
		}
		l2.print();
		l1.minus(l2);
		s1.Minus(s2);
		cout << "�����������:";
		l1.print();
		cout << "˳����������:";
		s1.print();
		break;
	}
	case 5: {
		int dimension;
		int x1[100];
		int x2[100];
		cout << "������������ά��:" << endl;
		cin >> dimension;
		cout << "�������һ������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x1[i];
		}
		cout << "������ڶ�������:" << endl;
		for (int i = 0; i < dimension; i++) {
			cin >> x2[i];
		}
		Vector v1(dimension, x1);
		Vector v2(dimension, x2);

		cout << "�������нǵ�����ֵΪ:" << v1.getCosAngle(v2) << endl;

		break;
	}
	case 6: {
		int d;
		int num;
		List l;
		cout << "������ԭʼ����ʽ������:" << endl;
		cin >> d;
		for (int i = 0; i < d; i++) {
			double coef;
			int expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l.addNode(ListNode(coef, expn));
		}
		l.print();
		cout << "�������󵼴���:" << endl;
		cin >> num;
		for (int i = 0; i < num; i++) {
			l.Derivation();
		}
		cout << "�󵼽����:";
		l.print();
		break;
	}
	case 7: {
		int d1, d2;
		List l1, l2, result;
		cout << "��һ������ʽ�м���:" << endl;
		cin >> d1;
		for (int i = 0; i < d1; i++) {
			int coef, expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l1.addNode(ListNode(coef, expn));
		}
		l1.print();
		cout << "�ڶ�������ʽ�м���:" << endl;
		cin >> d2;
		for (int i = 0; i < d2; i++) {
			int coef, expn;
			cout << "��ָ���ɸߵ���˳��,�������" << i + 1 << "��(ϵ�� ָ��):" << endl;
			cin >> coef >> expn;
			l2.addNode(ListNode(coef, expn));
		}
		l2.print();
		l1.multiply(l2, result);
		cout << "��������:";
		result.print();
		break;
	}
	case 8: {
		string exp;
		cout << "����������������ʽ" << endl;
		cin >> exp;
		Arithmetic ari(exp);
		cout << "��������: " << ari.getResult() << endl;
		break;
	}
	case 9: {
		string exp;
		string VarName;
		double Val;
		cout << "�����������" << endl;
		cin >> VarName;
		cout << "��������ʽ" << endl;
		cin >> exp;
		cout << "�����������ֵ" << endl;
		cin >> Val;
		ArithmeticX ariX(exp, VarName);
		auto ari = ariX.Assign(Val);
		cout << "��������: " << ari.getResult() << endl;
		break;
	}
	case 10: {
		cout << "���Կ�ʼ����ָ����" << endl;
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
						cout << "�����: ";
						(*it)->RUN(val);
						break;
					}
					if (it == funcs.end()) cout << "û���ҵ���Ӧ����" << endl;
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
				cout << "û�ж�Ӧָ��" << endl;
			}

			getline(cin, instruction);
		}
		break;
	}
	case 11: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "����������������С�����" << endl;
		cin >> row >> col;
		cout << "�������һ������" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "������ڶ�������" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, row, col);
		mat1.add(mat2);
		cout << "�����:" << endl;
		mat1.print();
		break;
	}
	case 12: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "����������������С�����" << endl;
		cin >> row >> col;
		cout << "�������һ������" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "������ڶ�������" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, row, col);
		mat1.minus(mat2);
		cout << "�����:" << endl;
		mat1.print();
		break;
	}
	case 13: {
		double data1[100][100];
		double data2[100][100];
		int row, col;
		cout << "�������һ��������С�����" << endl;
		cin >> row >> col;
		cout << "�������һ������" << endl;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				cin >> data1[i][j];
			}
		}
		cout << "������ڶ�������" << endl;
		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				cin >> data2[i][j];
			}
		}
		Matrix mat1(data1, row, col);
		Matrix mat2(data2, col, row);
		auto rtn = mat1.multiply(mat2);
		cout << "�����:" << endl;
		rtn->print();
		break;
	}
	case 14: {
		int row, col;
		double data[100][100];
		cout << "�����������С�����" << endl;
		cin >> row >> col;
		cout << "���������" << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cin >> data[i][j];
			}
		}
		Matrix mat(data, row, col);
		cout << "�����:" << endl;
		mat.Transpose();
		mat.print();
		break;
	}
	case 15: {
		int rc;
		double data[100][100];
		cout << "��������������" << endl;
		cin >> rc;
		cout << "���������" << endl;
		for (int i = 0; i < rc; i++) {
			for (int j = 0; j < rc; j++) {
				cin >> data[i][j];
			}
		}
		Matrix mat(data, rc, rc);
		cout << "�����:" << endl << mat.CalcDeterminant() << endl;
		break;
	}
	case 16: {
		//int rc;
		//double data[100][100];
		//cout << "��������������" << endl;
		//cin >> rc;
		//cout << "���������" << endl;
		//for (int i = 0; i < rc; i++) {
		//	for (int j = 0; j < rc; j++) {
		//		cin >> data[i][j];
		//	}
		//}
		//Matrix mat(data, rc, rc);
		//cout << "�����:" << endl;
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
	int dim = 11;//ά��
	int x1[100] = { 2, -45, 32, -245, 0, 3442, 5, 0, 25, 56, -23 };//����1
	int x2[100] = { 8, 90, 55, -3, 0, 67, 790, 234, 804, 0, -687 };//����2
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
		cout << "�������󵼴���:" << endl;
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

