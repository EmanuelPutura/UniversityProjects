//
// Created by Emanuel on 27.03.2021.
//

#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>
#include <string>
#include <map>

/*
 * Iterator for the DirectedGraph class
 */
class DirectedGraphIterator {
    friend class DirectedGraph;
private:
    std::vector<int> data;
    int current;

    explicit DirectedGraphIterator(const std::vector<int>& data) : data(data), current(0) {}
public:
    void first();
    void next();
    int getCurrent();
    bool isValid() const;
};

/*
 * DirectedGraph class
 */
class DirectedGraph {
    friend class DirectedGraphIterator;
private:
    std::map<int, std::vector<int>> vertices_in, vertices_out;
    std::map<std::pair<int, int>, int> edges_cost;
public:
    /*
     * Constructor of the class
     */
    explicit DirectedGraph(int vertices = 0);

    /*
     * Copy constructor of the class
     */
    DirectedGraph(DirectedGraph& other);

    /*
     * Adds a vertex to the graph
     * :param vertex: the vertex to be added
     * :throws: an exception if the vertex does not exist
     */
    void addVertex(const int& vertex);

    /*
     * Removes a vertex of the graph
     * :param vertex: the vertex to be removed
     * :throws: an exception if the vertex does not exist
     */
    void removeVertex(const int& vertex);

    /*
     * Adds an edge to the graph
     * :param edge_x: the start vertex of the edge
     * :param edge_y: the end vertex of the edge
     * :param cost: the cost of the edge
     * :throws: an exception if the vertices and/or the edge do not exist
     */
    void addEdge(const int& edge_x, const int& edge_y, const int& cost);

    /*
     * Removes an edge of the graph
     * :param edge_x: the start vertex of the edge
     * :param edge_y: the end vertex of the edge
     * :throws: an exception if the vertices and/or the edge do not exist
     */
    void removeEdge(const int& edge_x, const int& edge_y);

    /*
     * Searched for a vertex in the graph
     * :param vertex: a vertex in the graph
     * :returns: true if the vertex was found, false else
     */
    bool search(const int& vertex) const;

    /*
     * Tests if two vertices form an edge
     * :param edge_x: the start vertex of the edge
     * :param edge_y: the end vertex of the edge
     * :return: true if the vertices form an edge, false else
     * :raises: an exception if the given vertices do not exist
     */
    bool isEdge(const int& edge_x, const int& edge_y);

    /*
     * Gets the in degree of a vertex
     * :param vertex: a vertex of the graph
     * :return: the in degree of a vertex
     * :throws: an exception if the given vertex is not valid
     */
    int getInDegree(const int& vertex);

    /*
     * Gets the out degree of a vertex
     * :param vertex: a vertex of the graph
     * :return: the out degree of a vertex
     * :throws: an exception if the given vertex is not valid
     */
    int getOutDegree(const int& vertex);

    /*
     * Gets the cost of an edge
     * :param edge_x: the start vertex of the edge
     * :param edge_y: the end vertex of the edge
     * :return: the cost of the given edge
     * :throws: an exception if the edge does not exist
     */
    int getCost(const int& edge_x, const int& edge_y);

    /*
     * Sets the cost of an edge
     * :param edge_x: the start vertex of the edge
     * :param edge_y: the end vertex of the edge
     * :param cost: the new cost of the edge
     * :throws: an exception if the edge does not exist
     */
    void setCost(const int& edge_x, const int& edge_y, const int& cost);

    /*
     * Parses the vertices of the graph
     * :return: an iterator for parsing the vertices of the graph
     */
    DirectedGraphIterator parseVertices() const;

    /*
     * Parses the outbound neighbours of a given vertex
     * :param vertex: a vertex of the graph
     * :return: an iterator for parsing the outbound neighbours of a given vertex
     * :throws: an exception if the given vertex is not valid
     */
    DirectedGraphIterator parseVerticesOut(const int& vertex);

    /*
     * Parses the inbound neighbours of a given vertex
     * :param vertex: a vertex of the graph
     * :return: an iterator for parsing the inbound neighbours of a given vertex
     * :throws: an exception if the given vertex is not valid
     */
    DirectedGraphIterator parseVerticesIn(const int& vertex);

    /*
     * Inline getters
     */
    inline int getVerticesNo() const { return vertices_out.size(); }
    inline int getEdgesNo() const { return edges_cost.size(); }
};

#endif
