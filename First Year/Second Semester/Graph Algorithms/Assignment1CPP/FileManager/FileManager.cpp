//
// Created by Emanuel on 28.03.2021.
//

#include "FileManager.h"

#include <iostream>
#include <fstream>

DirectedGraph FileManager::read(const std::string &file_path) const {
    std::ifstream fin;
    fin.open(file_path);
    int vertices {0}, edges {0}, edge_x {0}, edge_y {0}, cost {0};

    fin >> vertices >> edges;
    DirectedGraph graph {vertices};

    for (size_t i = 0; i < edges; ++i) {
        fin >> edge_x >> edge_y >> cost;
        graph.addEdge(edge_x, edge_y, cost);
    }

    fin.close();
    return graph;
}

void FileManager::write(DirectedGraph graph, const std::string &file_path) {
    std::ofstream fout;
    fout.open(file_path);
    std::string file_data = "";

    file_data += std::to_string(graph.getVerticesNo()) + " " + std::to_string(graph.getEdgesNo()) + "\n";
    std::vector<int> isolated_nodes;

    auto vertices_it = graph.parseVertices();
    while (vertices_it.isValid()) {
        int vertex = vertices_it.getCurrent();
        if (!graph.getOutDegree(vertex))
            isolated_nodes.push_back(vertex);
        auto out_it = graph.parseVerticesOut(vertex);
        while (out_it.isValid()) {
            int neighbour = out_it.getCurrent();
            file_data += std::to_string(vertex) + " " + std::to_string(neighbour) + " " + std::to_string(graph.getCost(vertex, neighbour)) + "\n";
            out_it.next();
        }
        vertices_it.next();
    }

    for (const auto& node : isolated_nodes)
        file_data += std::to_string(node) + "\n";
    fout << file_data;

    fout.close();
}
