#include <iostream>
#include "testing/TestAll.h"
#include "presentation/consoleUI/ConsoleUI.h"
#include "examples/stl_examples/StlExamples.h"

int main() {
    TestAll testAll;
    testAll.testAll();

    TestSTL stlTest;
    stlTest.testSTLAll();

//    ConsoleUI consoleUI;
//    consoleUI.run();

    return 0;
}
