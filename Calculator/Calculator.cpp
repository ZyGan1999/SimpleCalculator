#include "Sequence.h"
#include "List.h"
#include "Vector.h"
#include "Operate.h"
#include "Arithmetic.h"
int main()
{
	//while (true) {
	//	Operate::printMenu();
	//	int c;
	//	cin >> c;
	//	//Operate::FunctionBox(c);
	//	Operate::test(c);
	//	system("pause");
	//	system("cls");
	//}
	Arithmetic a("12 5 /", 0);
	cout << a.getResult() << endl;
	while (1);
    return 0;
}

