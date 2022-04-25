//
// Created by Emanuel on 28.03.2021.
//

#ifndef GRAPHRANDOMGENERATOR_H
#define GRAPHRANDOMGENERATOR_H

#include "../DirectedGraph/DirectedGraph.h"

class GraphRandomGenerator {
public:
    /*
     * Generates a random graph
     * :param vertices: number of vertices for the generated graph
     * :param edges: number of edges for the generated graph
     * :return: the generated graph
     * :throws: an exception if the graph cannot be generated
     */
    DirectedGraph generateGraph(const int& vertices, const int& edges) const;
};

#endif
