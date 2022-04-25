#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
	testAll();
	testAllExtended();
	std::cout << "Finished LP Tests!" << std::endl;
	system("pause");
}
