#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

#include <crtdbg.h>
#include <stack>
#include <iostream>
using namespace std;


int main() {

	testAll();
	testAllExtended();

	int r = _CrtDumpMemoryLeaks();
	std::cout << "\nMemory Leaks: " << r << '\n';

	cout << "That's all!" << endl;
	system("pause");
}



