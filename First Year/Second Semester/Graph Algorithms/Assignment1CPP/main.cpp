#include "Testing/TestAll.h"
#include "ConsoleUI/ConsoleUI.h"

int main() {
    TestAll().testAll();

    ConsoleUI consoleUI;
    consoleUI.run();

    return 0;
}
