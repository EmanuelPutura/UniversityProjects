//
// Created by Emanuel on 28.03.2021.
//

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include "../DirectedGraph/DirectedGraph.h"

class ConsoleUI {
private:
    DirectedGraph directed_graph;

    std::string getCommand() const;
    std::string getUserData(const std::string& message) const;
    int mapCommand(const std::string& command) const;
    void menu() const;
public:
    void createRandomGraph();

    void readGraphFromTextFile();

    void writeGraphToTextFile();

    void getVerticesNo() const;

    void displayAllVertices() const;

    void testEdge();

    void displayInOutDegree();

    void displayOutboundEdges();

    void displayInboundEdges();

    void getCost();

    void setCost();

    void addEdge();

    void removeEdge();

    void addVertex();

    void removeVertex();

    void run();

    bool isPositiveInteger(const std::string& string) const;
};

#endif
