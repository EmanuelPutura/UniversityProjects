#include <iostream>
#include <crtdbg.h>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	std::cout << "Short tests are over!\n";

	testAllExtended();
    std::cout<<"Finished SMM Tests!"<<std::endl;
	
	int r = _CrtDumpMemoryLeaks();
	std::cout << "\nMemory Leaks: " << r << '\n';

	system("pause");
}
