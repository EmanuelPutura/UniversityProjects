//
// Created by Emanuel on 28.03.2021.
//

#include "ConsoleUI.h"
#include "../GraphGenerator/GraphRandomGenerator.h"
#include "../FileManager/FileManager.h"
#include "../TextTable/TextTable.h"

#include <iostream>

std::string ConsoleUI::getCommand() const {
    std::string command;
    std::cout << "command > ";
    std::getline(std::cin, command);
    std::cout << '\n';
    return command;
}

std::string ConsoleUI::getUserData(const std::string &message) const {
    std::string user_data;
    std::cout << message << "\n> ";
    std::getline(std::cin, user_data);
    std::cout << '\n';
    return user_data;
}

int ConsoleUI::mapCommand(const std::string &command) const {
    std::string commands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
    int int_commands[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    for (size_t i = 0; i < 16; ++i)
        if (command == commands[i]) return int_commands[i];
    return -1;
}

void ConsoleUI::createRandomGraph() {
    std::string vertices = getUserData("Please input the number of vertices of the graph: ");
    std::string edges = getUserData("Please input the number of edges of the graph: ");

    if (!isPositiveInteger(vertices) || !isPositiveInteger(edges)) {
        std::cout << "Invalid vertices/edges number.\n";
        return;
    }

    try {
        GraphRandomGenerator generator;
        directed_graph = generator.generateGraph(stoi(vertices), stoi(edges));
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::readGraphFromTextFile() {
    std::string file_path = "../Files/";
    file_path += getUserData("Please input the name of the input file: ");

    try {
        FileManager file_manager;
        directed_graph = file_manager.read(file_path);
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::writeGraphToTextFile() {
    std::string file_path = "../Files/";
    file_path += getUserData("Please input the name of the output file: ");

    try {
        FileManager file_manager;
        file_manager.write(directed_graph, file_path);
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::getVerticesNo() const {
    int vertices_no = directed_graph.getVerticesNo();
    std::cout << "There are " << vertices_no << " vertices in the graph.\n";
}

void ConsoleUI::displayAllVertices() const {
    std::cout << "The vertices of the graph are:\n";
    std::string vertices_str = "";

    auto it = directed_graph.parseVertices();
    while (it.isValid()) {
        vertices_str += std::to_string(it.getCurrent()) + ", ";
        it.next();
    }
    vertices_str.pop_back();
    vertices_str.pop_back();
    std::cout << vertices_str << '\n';
}

void ConsoleUI::testEdge() {
    std::string edge_x = getUserData("Please input the source vertex: ");
    std::string edge_y = getUserData("Please input the destination vertex: ");

    if (!isPositiveInteger(edge_x) || !isPositiveInteger(edge_y)) {
        std::cout << "Invalid vertices.\n";
        return;
    }

    try {
        std::string message = directed_graph.isEdge(stoi(edge_x), stoi(edge_y)) ? "form" : "do not form";
        std::cout << "The two vertices " << message << " an edge.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::displayInOutDegree() {
    std::string vertex = getUserData("Please input a vertex: ");
    if (!isPositiveInteger(vertex)) {
        std::cout << "Invalid vertex.\n";
        return;
    }

    try {
        int in_degree = directed_graph.getInDegree(stoi(vertex));
        int out_degree = directed_graph.getOutDegree(stoi(vertex));
        std::cout << "The in degree of the given vertex is " << in_degree << ".\n";
        std::cout << "The out degree of the given vertex is " << out_degree << ".\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::displayOutboundEdges() {
    std::string vertex = getUserData("Please input a vertex: ");
    if (!isPositiveInteger(vertex)) {
        std::cout << "Invalid vertex.\n";
        return;
    }

    std::cout << "The outbound edges of the vertex " << vertex << " are:\n";
    try {
        auto it = directed_graph.parseVerticesOut(stoi(vertex));
        while (it.isValid()) {
            std::cout << "(" << vertex << ", " << std::to_string(it.getCurrent()) << ")\n";
            it.next();
        }
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::displayInboundEdges() {
    std::string vertex = getUserData("Please input a vertex: ");
    if (!isPositiveInteger(vertex)) {
        std::cout << "Invalid vertex.\n";
        return;
    }

    std::cout << "The inbound edges of the vertex " << vertex << " are:\n";
    try {
        auto it = directed_graph.parseVerticesIn(stoi(vertex));
        while (it.isValid()) {
            std::cout << "(" << std::to_string(it.getCurrent()) << ", " << vertex << ")\n";
            it.next();
        }
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::getCost() {
    std::string edge_x = getUserData("Please input the source vertex of the edge: ");
    std::string edge_y = getUserData("Please input the destination vertex of the edge: ");

    if (!isPositiveInteger(edge_x) || !isPositiveInteger(edge_y)) {
        std::cout << "Invalid vertices.\n";
        return;
    }

    try {
        int cost = directed_graph.getCost(stoi(edge_x), stoi(edge_y));
        std::cout << "The cost associated to the edge (" << edge_x << ", " << edge_y << ") is " << cost << ".\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::setCost() {
    std::string edge_x = getUserData("Please input the source vertex of the edge: ");
    std::string edge_y = getUserData("Please input the destination vertex of the edge: ");
    std::string cost = getUserData("Please input the cost associated to the edge: ");

    if (!isPositiveInteger(edge_x) || !isPositiveInteger(edge_y)) {
        std::cout << "Invalid vertices.\n";
        return;
    }
    if (!isPositiveInteger(cost)) {
        std::cout << "Invalid edge cost.\n";
        return;
    }

    try {
        directed_graph.setCost(stoi(edge_x), stoi(edge_y), stoi(cost));
        std::cout << "The cost associated to the edge (" << edge_x << ", " << edge_y << ") 1was update.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::addEdge() {
    std::string edge_x = getUserData("Please input the source vertex of the edge: ");
    std::string edge_y = getUserData("Please input the destination vertex of the edge: ");
    std::string cost = getUserData("Please input the cost associated to the edge: ");

    if (!isPositiveInteger(edge_x) || !isPositiveInteger(edge_y)) {
        std::cout << "Invalid vertices.\n";
        return;
    }
    if (!isPositiveInteger(cost)) {
        std::cout << "Invalid edge cost.\n";
        return;
    }

    try {
        directed_graph.addEdge(stoi(edge_x), stoi(edge_y), stoi(cost));
        std::cout << "The edge (" << edge_x << ", " << edge_y << ") was added.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::removeEdge() {
    std::string edge_x = getUserData("Please input the source vertex of the edge: ");
    std::string edge_y = getUserData("Please input the destination vertex of the edge: ");

    if (!isPositiveInteger(edge_x) || !isPositiveInteger(edge_y)) {
        std::cout << "Invalid vertices.\n";
        return;
    }

    try {
        directed_graph.removeEdge(stoi(edge_x), stoi(edge_y));
        std::cout << "The edge (" << edge_x << ", " << edge_y << ") was removed.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::addVertex() {
    std::string vertex = getUserData("Please input a vertex: ");
    if (!isPositiveInteger(vertex)) {
        std::cout << "Invalid vertex.\n";
        return;
    }

    try {
        directed_graph.addVertex(stoi(vertex));
        std::cout << "The vertex " << vertex << " was added.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::removeVertex() {
    std::string vertex = getUserData("Please input a vertex: ");
    if (!isPositiveInteger(vertex)) {
        std::cout << "Invalid vertex.\n";
        return;
    }

    try {
        directed_graph.removeVertex(stoi(vertex));
        std::cout << "The vertex " << vertex << " was removed.\n";
    }
    catch (std::string error) {
        std::cout << error << '\n';
    }
}

void ConsoleUI::menu() const {
    TextTable table {2};
    table.addHeader(2, "COMMAND", "COMMAND DESCRIPTION");
    std::string commands[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
    std::string command_descriptions[] = {"create a new random graph", "read a graph from a text file", "write the graph to a text file",
                                          "get the number of vertices in the graph", "display all the vertices in the graph",
                                          "test if there is an edge between two vertices", "display the in/out degree of a vertex",
                                          "display the outbound edges of a vertex", "display the inbound edges of a vertex", "get cost of an edge",
                                          "set cost of an edge", "add an edge", "remove an edge", "add a vertex", "remove a vertex",
                                          "exit the application"};
    for (size_t i = 0; i < 16; ++i)
        table.addRow(2, commands[i].c_str(), command_descriptions[i].c_str());
    std::cout << "Application Menu:\n" << table << '\n';
}

void ConsoleUI::run() {
    bool running = true;
    while (running) {
        try {
            menu();

            int command = mapCommand(getCommand());
            switch (command) {
                case 0:
                    createRandomGraph();
                    break;
                case 1:
                    readGraphFromTextFile();
                    break;
                case 2:
                    writeGraphToTextFile();
                    break;
                case 3:
                    getVerticesNo();
                    break;
                case 4:
                    displayAllVertices();
                    break;
                case 5:
                    testEdge();
                    break;
                case 6:
                    displayInOutDegree();
                    break;
                case 7:
                    displayOutboundEdges();
                    break;
                case 8:
                    displayInboundEdges();
                    break;
                case 9:
                    getCost();
                    break;
                case 10:
                    setCost();
                    break;
                case 11:
                    addEdge();
                    break;
                case 12:
                    removeEdge();
                    break;
                case 13:
                    addVertex();
                    break;
                case 14:
                    removeVertex();
                    break;
                case 15:
                    running = false;
                    break;
                default:
                    std::cout << "Invalid command.\n";
                    break;
            }
        }
        catch (...) {
            std::cout << "Unexpected error occurred.\n";
        }
    }
}

bool ConsoleUI::isPositiveInteger(const std::string& string) const {
    for (size_t i = 0; i < string.length(); ++i)
        if (!isdigit(string[i])) return false;
    return true;
}
