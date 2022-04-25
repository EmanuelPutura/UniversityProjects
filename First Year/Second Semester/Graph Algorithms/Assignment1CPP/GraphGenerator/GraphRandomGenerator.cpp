//
// Created by Emanuel on 28.03.2021.
//

#include "GraphRandomGenerator.h"

#include <vector>
#include <algorithm>

DirectedGraph GraphRandomGenerator::generateGraph(const int &vertices, const int &edges) const {
    if (edges > vertices * vertices)
        throw std::string("Invalid number of edges (too many).\n");

    std::vector<std::tuple<int, int, int>> all_edges;
    for (size_t x = 0; x < vertices; ++x)
        for (size_t y = 0; y < vertices; ++y) {
            int cost = rand() % 100;
            all_edges.push_back({x, y, cost});
        }
    int shuffle_cnt = rand() % 10;
    for (size_t i = 0; i < shuffle_cnt; ++i)
        std::random_shuffle(all_edges.begin(), all_edges.end());

        DirectedGraph graph {vertices};
        for (size_t i = 0; i < edges; ++i)
            graph.addEdge(std::get<0>(all_edges[i]), std::get<1>(all_edges[i]), std::get<2>(all_edges[i]));
        return graph;
}
