//
// Created by Emanuel on 27.03.2021.
//

#include "DirectedGraph.h"

#include <algorithm>

DirectedGraph::DirectedGraph(int vertices) {
    if (vertices < 0)
        throw std::string("Invalid number of vertices.\n");
    for (size_t i = 0; i < vertices; ++i)
        addVertex(i);
}

DirectedGraph::DirectedGraph(DirectedGraph &other) {
    vertices_in.clear();
    vertices_out.clear();
    edges_cost.clear();

    // add the vertices
    auto vertices_it = other.parseVertices();
    while(vertices_it.isValid()) {
        int vertex = vertices_it.getCurrent();
        addVertex(vertex);
        vertices_it.next();
    }

    // add the edges
    vertices_it.first();
    while(vertices_it.isValid()) {
        int vertex = vertices_it.getCurrent();
        auto out_it = other.parseVerticesOut(vertex);
        while(out_it.isValid()) {
            int edge_y = out_it.getCurrent();
            int cost = other.getCost(vertex, edge_y);
            addEdge(vertex, edge_y, cost);
            out_it.next();
        }
        vertices_it.next();
    }
}

void DirectedGraph::addVertex(const int &vertex) {
    if (search(vertex))
        throw std::string("The vertex was already added.\\n");
    vertices_out.insert({vertex, std::vector<int>()});
    vertices_in.insert({vertex, std::vector<int>()});
}

void DirectedGraph::removeVertex(const int &vertex) {
    if (!search(vertex))
        throw std::string("The vertex was not found.\n");

    for (const auto& edge_y : vertices_out[vertex]) {
        edges_cost.erase(std::pair<int, int>(vertex, edge_y));
        vertices_in[edge_y].erase(std::remove(vertices_in[edge_y].begin(), vertices_in[edge_y].end(), vertex), vertices_in[edge_y].end());
    }

    for (const auto& edge_x : vertices_in[vertex]) {
        edges_cost.erase(std::pair<int, int>(edge_x, vertex));
        vertices_out[edge_x].erase(std::remove(vertices_out[edge_x].begin(), vertices_out[edge_x].end(), vertex), vertices_out[edge_x].end());
    }

    vertices_out.erase(vertex);
    vertices_in.erase(vertex);
}

void DirectedGraph::addEdge(const int &edge_x, const int &edge_y, const int &cost) {
    if (!search(edge_x) || !search(edge_y))
        throw std::string("Invalid vertices.\n");
    if (isEdge(edge_x, edge_y))
        throw std::string("Edge already exists.\n");
    vertices_out[edge_x].push_back(edge_y);
    vertices_in[edge_y].push_back(edge_x);
    edges_cost[std::pair<int, int>(edge_x, edge_y)] = cost;
}

void DirectedGraph::removeEdge(const int &edge_x, const int &edge_y) {
    if (!search(edge_x) || !search(edge_y))
        throw std::string("Invalid vertices.\n");
    if (!isEdge(edge_x, edge_y))
        throw std::string("Edge does not exist.\n");
    vertices_out[edge_x].erase(std::remove(vertices_out[edge_x].begin(), vertices_out[edge_x].end(), edge_y), vertices_out[edge_x].end());
    vertices_in[edge_y].erase(std::remove(vertices_in[edge_y].begin(), vertices_in[edge_y].end(), edge_x), vertices_in[edge_y].end());
    edges_cost.erase(std::pair<int, int>(edge_x, edge_y));
}

bool DirectedGraph::search(const int &vertex) const {
    for (const auto &kv : vertices_out)
        if (kv.first == vertex) return true;
    return false;
}

bool DirectedGraph::isEdge(const int &edge_x, const int &edge_y) {
    if (!search(edge_x) || !search(edge_y))
        throw std::string("Invalid vertices.\n");
    return std::find(vertices_out[edge_x].begin(), vertices_out[edge_x].end(), edge_y) != vertices_out[edge_x].end();
}

int DirectedGraph::getInDegree(const int &vertex) {
    if (!search(vertex))
        throw std::string("Invalid vertex.\n");
    return vertices_in[vertex].size();
}

int DirectedGraph::getOutDegree(const int &vertex) {
    if (!search(vertex))
        throw std::string("Invalid vertex.\n");
    return vertices_out[vertex].size();
}

int DirectedGraph::getCost(const int &edge_x, const int &edge_y) {
    if (!isEdge(edge_x, edge_y))
        throw std::string("The edge was not found.\n");
    return edges_cost[std::pair<int, int>(edge_x, edge_y)];
}

void DirectedGraph::setCost(const int &edge_x, const int &edge_y, const int &cost) {
    if (!isEdge(edge_x, edge_y))
        throw std::string("The edge was not found.\n");
    edges_cost[std::pair<int, int>(edge_x, edge_y)] = cost;
}

DirectedGraphIterator DirectedGraph::parseVertices() const {
    std::vector<int> vertices;
    for (const auto& key : vertices_out)
        vertices.push_back(key.first);
    return DirectedGraphIterator(vertices);
}

DirectedGraphIterator DirectedGraph::parseVerticesOut(const int &vertex) {
    return DirectedGraphIterator(vertices_out[vertex]);
}

DirectedGraphIterator DirectedGraph::parseVerticesIn(const int &vertex) {
    return DirectedGraphIterator(vertices_in[vertex]);
}

// ------------------ Directed Graph Iterator ------------------

void DirectedGraphIterator::first() {
    current = 0;
}

void DirectedGraphIterator::next() {
    if (current >= data.size())
        throw std::exception();
    current++;
}

int DirectedGraphIterator::getCurrent() {
    if (current >= data.size())
        throw std::exception();
    return data[current];
}

bool DirectedGraphIterator::isValid() const {
    return current < data.size();
}
