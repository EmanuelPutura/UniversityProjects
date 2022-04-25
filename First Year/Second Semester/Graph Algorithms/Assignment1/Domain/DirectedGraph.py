import copy


class DirectedGraphException(Exception):
    """
        Handles exceptions related to the DirectedGraph class
    """
    pass


class GraphIterator:
    """
        Provides an iterator for the DirectedGraph class
    """
    def __init__(self, data):
        self.__data = data
        self.__position = -1

    def __iter__(self):
        return self

    def __next__(self):
        self.__position += 1
        if self.__position == len(self.__data):
            raise StopIteration()
        return self.__data[self.__position]


class DirectedGraph:
    """
        DirectedGraph class
    """
    def __init__(self, vertices=0):
        self.__vertices_in = {}  # inbound neighbours
        self.__vertices_out = {}  # outbound neighbours
        self.__edges_cost = {}  # a dictionary that associates to an edge an integer value (for instance, a cost)
        self.__addDefaultVertices(vertices)

    @property
    def edges_cost(self):
        return self.__edges_cost

    @edges_cost.setter
    def edges_cost(self, other):
        self.__edges_cost = other

    @property
    def vertices_in(self):
        return self.__vertices_in

    @vertices_in.setter
    def vertices_in(self, other):
        self.__vertices_in = other

    @property
    def vertices_out(self):
        return self.__vertices_out

    @vertices_out.setter
    def vertices_out(self, other):
        self.__vertices_out = other

    def __addDefaultVertices(self, vertices):
        """
            Adds a number of vertices to the graph
            :param vertices: the number of vertices to be added
            :raises: DirectedGraphException if the vertices number is negative
        """
        if vertices < 0:
            raise DirectedGraphException("Invalid number of vertices.\n")
        for i in range(vertices):
            self.addVertex(i)

    def getVerticesNo(self):
        """
            Gets the number of vertices of the graph
            :return: the number of vertices of the graph
        """
        return len(self.__vertices_out)

    def getEdgesNo(self):
        """
            Gets the number of edges of the graph
            :return: the number of edges of the graph
        """
        return len(self.__edges_cost)

    def isEdge(self, edge_x, edge_y):
        """
            Tests if two vertices form an edge
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :return: true if the vertices form an edge, false else
            :raises: DirectedGraphException if the given vertices do not exist
        """
        if edge_x not in self.__vertices_out.keys() or edge_y not in self.__vertices_in.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        return edge_y in self.__vertices_out[edge_x]

    def getInDegree(self, vertex):
        """
            Gets the in degree of a vertex
            :param vertex: a vertex of the graph
            :return: the in degree of a vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return len(self.__vertices_in[vertex])

    def getOutDegree(self, vertex):
        """
            Gets the out degree of a vertex
            :param vertex: a vertex of the graph
            :return: the out degree of a vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return len(self.__vertices_out[vertex])

    def parseVertices(self):
        """
            Parses the vertices of the graph
            :return: an iterator for parsing the vertices of the graph
        """
        return GraphIterator(list(self.__vertices_out.keys()))

    def parseVerticesOut(self, vertex):
        """
            Parses the outbound neighbours of a given vertex
            :param vertex: a vertex of the graph
            :return: an iterator for parsing the outbound neighbours of a given vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return GraphIterator(self.__vertices_out[vertex])

    def parseVerticesIn(self, vertex):
        """
            Parses the inbound neighbours of a given vertex
            :param vertex: a vertex of the graph
            :return: an iterator for parsing the inbound neighbours of a given vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return GraphIterator(self.__vertices_in[vertex])

    def getCost(self, edge_x, edge_y):
        """
            Gets the cost of an edge
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :return: the cost of the given edge
            :raises: DirectedGraphException if the edge does not exist
        """
        if not self.isEdge(edge_x, edge_y):
            raise DirectedGraphException("The edge was not found.\n")
        return self.__edges_cost[(edge_x, edge_y)]

    def setCost(self, edge_x, edge_y, cost):
        """
            Sets the cost of an edge
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :param cost: the new cost of the edge
            :raises: DirectedGraphException if the edge does not exist
        """
        if not self.isEdge(edge_x, edge_y):
            raise DirectedGraphException("The edge was not found.\n")
        self.__edges_cost[(edge_x, edge_y)] = cost

    def addEdge(self, edge_x, edge_y, cost):
        """
            Adds an edge to the graph
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :param cost: the cost of the edge
            :raises: DirectedGraphException if the vertices and/or the edge do not exist
        """
        if edge_x not in self.__vertices_out.keys() or edge_y not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        if edge_y in self.__vertices_out[edge_x]:
            raise DirectedGraphException("Edge already exists.\n")
        self.__vertices_out[edge_x].append(edge_y)
        self.__vertices_in[edge_y].append(edge_x)
        self.__edges_cost[(edge_x, edge_y)] = cost

    def removeEdge(self, edge_x, edge_y):
        """
            Removes an edge of the graph
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :raises: DirectedGraphException if the vertices and/or the edge do not exist
        """
        if edge_x not in self.__vertices_out.keys() or edge_y not in self.__vertices_out.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        if edge_y not in self.__vertices_out[edge_x]:
            raise DirectedGraphException("Edge does not exist.\n")
        self.__vertices_out[edge_x].remove(edge_y)
        self.__vertices_in[edge_y].remove(edge_x)
        del self.__edges_cost[(edge_x, edge_y)]

    def addVertex(self, vertex):
        """
            Adds a vertex to the graph
            :param vertex: the vertex to be added
            :raises: DirectedGraphException if the vertex does not exist
        """
        if vertex in self.__vertices_out.keys():
            raise DirectedGraphException("The vertex was already added.\n")
        self.__vertices_out[vertex] = []
        self.__vertices_in[vertex] = []

    def removeVertex(self, vertex):
        """
            Removes a vertex of the graph
            :param vertex: the vertex to be removed
            :raises: DirectedGraphException if the vertex does not exist
        """
        if vertex not in self.__vertices_out.keys():
            raise DirectedGraphException("The vertex was not found.\n")
        for edge_y in self.__vertices_out[vertex]:
            del self.__edges_cost[(vertex, edge_y)]
            self.__vertices_in[edge_y].remove(vertex)
        for edge_x in self.__vertices_in[vertex]:
            del self.__edges_cost[(edge_x, vertex)]
            self.__vertices_out[edge_x].remove(vertex)
        del self.__vertices_out[vertex]
        del self.__vertices_in[vertex]

    def copyGraph(self):
        """
            Gets a copy of the graph
            :return: a copy of the graph
        """
        graph = DirectedGraph(self.getVerticesNo())
        graph.__edges_cost = copy.deepcopy(self.__edges_cost)
        for vertex in self.parseVertices():
            graph.__vertices_in[vertex] = copy.deepcopy(self.__vertices_in[vertex])
            graph.__vertices_out[vertex] = copy.deepcopy(self.__vertices_out[vertex])
        return graph
