//
// Created by Emanuel on 28.03.2021.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../DirectedGraph/DirectedGraph.h"

class FileManager {
public:
    /*
     * Reads graph data from a file
     * :param file_path: the path of the file
     * :return: the graph read from the file
     */
    DirectedGraph read(const std::string& file_path) const;

    /*
     * Writes graph data to a file
     * :param graph: the graph to be written into a file
     * :param file_path: the path to the file
     */
    void write(DirectedGraph graph, const std::string& file_path);
};

#endif
