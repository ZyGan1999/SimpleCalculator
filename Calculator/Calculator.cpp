#include "Sequence.h"
#include "List.h"
#include "Vector.h"
#include "Operate.h"
int main()
{
	while (true) {
		Operate::printMenu();
		int c;
		cin >> c;
		//Operate::FunctionBox(c);
		Operate::test(c);
		system("pause");
		system("cls");
	}
    return 0;
}

