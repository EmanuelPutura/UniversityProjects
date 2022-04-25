//
// Created by Emanuel on 20.03.2021.
//

#include <iostream>
#include "TextTable.h"

int main() {
    TextTable t{ 3 };
    t.addHeader(3, "Company Cool", "Company OK", "NO! Company");
    t.addRow(3, "Google", "Facebook", "AmazonAAAAAAAAAAAAAAAA");
    t.addRow(3, "GFFF", "FDDD", "AAAA");
    //t.addRow(3, "GFFF", "FDDDAAAAAAAAAAAAAAAAAAAAAAAA", "AAA");
    std::cout << t << '\n';
    
    return 0;
}
