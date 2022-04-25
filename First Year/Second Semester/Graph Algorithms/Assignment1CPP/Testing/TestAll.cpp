//
// Created by Emanuel on 28.03.2021.
//

#include "TestAll.h"
#include "../DirectedGraph/DirectedGraph.h"

#include <assert.h>
#include <iostream>

void TestAll::testAll() const {
    testDomain();
}

void TestAll::testDomain() const {
    DirectedGraph g {5};

    // test add edge
    g.addEdge(0, 0, 1);
    g.addEdge(0, 1, 7);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 1, -1);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 5);

    // test search
    for (size_t i = 0; i < 5; ++i)
        assert(g.search(i));
    for (size_t i = 5; i < 10; ++i)
        assert(!g.search(i));

    // test id edge
    assert(g.isEdge(0, 0));
    assert(g.isEdge(0, 1));
    assert(g.isEdge(2, 3));
    assert(!g.isEdge(3, 3));
    assert(!g.isEdge(4, 3));

    // test get in degree
    assert(g.getInDegree(1) == 2);
    assert(!g.getInDegree(4));

    // test get out degree
    assert(g.getOutDegree(2) == 2);

    // test get cost
    assert(g.getCost(1, 3) == 8);
    assert(g.getCost(2, 1) == -1);

    // test set cost
    g.setCost(2, 1, -50);
    assert(g.getCost(2, 1) == -50);

    // test get vertices no
    assert(g.getVerticesNo() == 5);

    // test get edges no
    assert(g.getEdgesNo() == 6);

    // test add vertex
    g.addVertex(100);
    assert(g.getVerticesNo() == 6);
    g.addVertex(10);
    assert(g.getVerticesNo() == 7);
    assert(g.getEdgesNo() == 6);

    // test remove vertex
    g.removeVertex(2);
    assert(g.getVerticesNo() == 6);
    assert(g.getEdgesNo() == 3);

    // test add edge
    g.addEdge(100, 3, 5);
    assert(g.getEdgesNo() == 4);
    assert(g.isEdge(100, 3));
    assert(g.getCost(100, 3) == 5);

    // test remove edge
    g.removeEdge(0, 1);
    assert(g.getEdgesNo() == 3);
    assert(!g.isEdge(0, 1));
}
