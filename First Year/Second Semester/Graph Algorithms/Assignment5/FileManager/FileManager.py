from Domain.DirectedGraph import DirectedGraph


class FileManager:
    @staticmethod
    def read(file_path, type=DirectedGraph):
        """
            Reads graph data from a file
            :param type: the type of the read graph
            :param file_path: the path of the file
            :return: the graph read from the file
        """
        with open(file_path, 'r') as text_file:
            vertices, edges = [int(data) for data in next(text_file).split()]  # read the first line
            graph = type(vertices)
            for edge in range(edges):  # read the edges
                edge_x, edge_y, cost = [int(data) for data in next(text_file).split()]  # read the next line
                graph.addEdge(edge_x, edge_y, cost)
        return graph

    @staticmethod
    def write(graph, file_path):
        """
            Writes graph data to a file
            :param graph: the graph to be written into a file
            :param file_path: the path to the file
        """
        vertices_no, edges_no = graph.getVerticesNo(), graph.getEdgesNo()
        file_data = str(vertices_no) + " " + str(edges_no) + "\n"

        isolated_nodes = []
        for vertex in graph.parseVertices():
            if not graph.getOutDegree(vertex):
                isolated_nodes.append(vertex)
            for neighbour in graph.parseVerticesOut(vertex):
                file_data += str(vertex) + " " + str(neighbour) + " " + str(graph.getCost(vertex, neighbour)) + "\n"
        for node in isolated_nodes:
            file_data += str(node) + "\n"

        with open(file_path, "w") as text_file:
            text_file.write(file_data)
