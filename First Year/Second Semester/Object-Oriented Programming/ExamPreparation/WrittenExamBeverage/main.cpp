#include <iostream>
#include "BeverageMachine.h"

int main() {
    BeverageMachine machine;

    machine.prepare("Tea", 0);
    machine.prepare("Coffee", 1);
    machine.prepare("Coffee", 2);

    return 0;
}
