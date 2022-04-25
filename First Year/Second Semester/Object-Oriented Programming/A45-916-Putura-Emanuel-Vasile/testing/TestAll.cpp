//
// Created by Emanuel on 20.03.2021.
//

#include "TestAll.h"
#include "../domain/TrenchCoat/TrenchCoat.h"
#include "../validation/CoatValidator.h"
#include "../business/CoatsService.h"
#include "../exceptions/ServiceException/ServiceException.h"

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

void Testing::TestAll::testAll() const {
    testDomain();
    testInfrastucture();
    testValidation();
    testBusiness();
}

void Testing::TestAll::testDomain() const {
    testTrenchCoat();
}

void Testing::TestAll::testTrenchCoat() const {
    TrenchCoat t1;

    // test default constructor and getters
    assert(t1.getSize() == "");
    assert(t1.getColour() == "");
    assert(t1.getPrice() == 0);
    assert(t1.getQuantity() == 0);
    assert(t1.getPhotograph() == "");

    // test getters
    TrenchCoat t2 {"XS", "black", 400, 10, "photograph ..."};
    assert(t2.getSize() == "XS");
    assert(t2.getColour() == "black");
    assert(t2.getPrice() == 400);
    assert(t2.getQuantity() == 10);
    assert(t2.getPhotograph() == "photograph ...");

    // test << operator
    std::stringbuf buffer; // use a buffer to store the output
    std::ostream os (&buffer);
    os << t2; // store the output in the buffer
    assert(buffer.str() == "XS black 400 10 photograph ...");

    // test == operator
    TrenchCoat t3 {"XS", "black", 400, 10, "photograph ..."};
    assert(t2 == t3);
}

void Testing::TestAll::testInfrastucture() const {
    testCoatsRepository();
}

void Testing::TestAll::testCoatsRepository() const {
    Repository<TrenchCoat> r;
    std::string colours[] = {"black", "red", "yellow", "blue", "white", "green", "blue", "gray", "white", "white"};
    std::string photographs[] = {"p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10"};

    // add some elements to the repository and test the add operation
    for (size_t i = 0; i < 10; ++i) {
        r.add(TrenchCoat("M", colours[i], i * 7, i * 10, photographs[i]));
        assert(r[i] == TrenchCoat("M", colours[i], i * 7, i * 10, photographs[i]));
    }

//    // test update function
//    assert(r.update(r.getData()[1], TrenchCoat("M", "purple")) == 1); // updated the element with index 1
//    assert(r.update(TrenchCoat(), TrenchCoat("M")) == -1); // no such element found
//    assert(r.getData()[1] == TrenchCoat("M", "purple"));
}

void Testing::TestAll::testValidation() const {
    testCoatValidator();
}

void Testing::TestAll::testCoatValidator() const {
    // test default cases for the coat validator
    TrenchCoat t1 = TrenchCoat();
    CoatValidator v;
    assert(!v.validate(t1));
    t1 = TrenchCoat("M", "black", 2, 3, "photo");
    assert(v.validate(t1));

    // test errors message for the coat validator
    t1 = TrenchCoat("XS", "black", 2, 3);
    assert(!v.validate(t1));
    assert(v.getErrors() == "Invalid trench coat photograph.\n");
}

void Testing::TestAll::testBusiness() const {
    testCoatsService();
}

void Testing::TestAll::testCoatsService() const {
    Repository<TrenchCoat> r, b;
    CoatsService s {r, b};

    // test service creation and getLength function
    assert(s.getLength() == 0);

    // test add function
    s.add("M", "black", 100, 20, "photo1");
    assert(s.getLength() == 1);

    // test << operator
    std::stringbuf buffer;
    std::ostream os (&buffer);
    os << s;
    assert (buffer.str() == std::string("M black 100 20 photo1\n"));

    // test getDataTextTable operation
    TextTable table = s.getDataTextTable(s.getData(), s.getLength());
    assert(table.getCellData(1, 0) == "1");
    assert(table.getCellData(1, 1) == "M");
    assert(table.getCellData(1, 2) == "black");
    assert(table.getCellData(1, 3) == "$100");
    assert(table.getCellData(1, 4) == "20");
    assert(table.getCellData(1, 5) == "photo1");

    // assert add exception
    try {
        s.add("M", "black", 100, 200, "photo1");
        assert(false);
    }
    catch (const ServiceException& exception) {
        assert(exception.getMessage() == "Attempted to add an existing element to the repository.\n");
    }
    // test exception throw for add function
    try {
        s.add("", "black", 100, 20, "photo");
        assert(false);
    }
    catch (const ServiceException& exception) {
        assert(exception.getMessage() == "Invalid trench coat size.\n");
    }

    s.add("XS", "gray", 500, 5, "photo2");
    assert(s.getLength() == 2);

    // test update function
    s.update("M", "black", 100, "photo1", "L", "black", 200, 20, "photo1");
    assert(s.getLength() == 2);
    s.update("L", "black", 200, "photo1", "L", "black", 300, 20, "photo1"); // should work fine

    // test exception throw for update function
    try {
        s.update("M", "black", 100, "photo1", "L", "black", 200, 20, "photo1");
        assert(false);
    }
    catch (const ServiceException& exception) {
        assert(exception.getMessage() == "The element was not found.\n");
    }

    // test remove function
    s.remove("L", "black", 300, "photo1");
    assert(s.getLength() == 1);

    // test exception throw for remove function
    try {
        s.remove("L", "black", 300, "photo1");
        assert(false);
    }
    catch (const ServiceException& exception) {
        assert(exception.getMessage() == "The element was not found.\n");
    }

    s.remove("XS", "gray", 500, "photo2");
    assert(s.getLength() == 0);

    try {
        s.addDefault();
    }
    catch (...) {
        return;
    }
    assert(s.getLength() == 10);

    assert(s.filterDataPerSize("M").size() == 1);
    assert(s.getCoatsPerSizeLength("M") == 1);
    s.addToShoppingBasket(2, "");
    assert(s.getPayment() == 1000);
    s.addToShoppingBasket(2, "");
    assert(s.getPayment() == 2000);
    s.addToShoppingBasket(8, "");
    assert(s.getPayment() == 2200);

    auto tb = s.getSingleCoatPerSizeTextTable(2, "");
    assert(tb.getCellData(1, 1) == "XS");

    auto tbl = s.getShoppingBasket();
    assert(tbl.getRowsNo() == 3);
    assert(tbl.getCellData(1, 1) == "XS");

    auto tbl2 = s.getSingleCoatTextTable(0, s.getData());
    assert(tbl2.getCellData(1, 1) == "3XS");

    s.add("M", "black", 100, 200, "a");
    s.launchBrowserSizeCoatPhoto(9, "");
}
