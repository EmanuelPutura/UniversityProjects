//
// Created by Emanuel on 04.04.2021.
//

#include "TestAll.h"
#include "../infrastructure/Repository/Repository.h"

#include <string>
#include <assert.h>

void TestAll::testRepository() {
    Repository<int> repo_ints;
    repo_ints.add(5);
    assert(repo_ints.getLength() == 1);
    try {
        repo_ints.update(2, 3);
        assert(false);
    }
    catch (std::exception) {
        assert(true);
        assert(repo_ints.getLength() == 1);
        assert(repo_ints[0] == 5);
    }

    repo_ints.add(2);
    repo_ints.add(6);
    repo_ints.add(1);

    try {
        repo_ints.update(6, 10);
        assert(repo_ints.getLength() == 4);
        assert(repo_ints[2] == 10);
        assert(repo_ints[3] == 1);
    }
    catch (std::exception) {
        assert(false);
    }

    try {
        assert(repo_ints[4] == 2);
        assert(false);
    }
    catch(...) {
        assert(true);
    }

    repo_ints.remove(10);
    assert(repo_ints.getLength() == 3);
    assert(repo_ints[2] == 1);

    assert(repo_ints.search(10) == -1);
    assert(repo_ints.search(1) == 2);
    assert(repo_ints.search(2) == 1);
}

void TestAll::testAll() {
    testRepository();
}

