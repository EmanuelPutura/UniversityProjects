import copy
import math
from queue import SimpleQueue


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
        self._vertices_in = {}  # inbound neighbours
        self._vertices_out = {}  # outbound neighbours
        self._edges_cost = {}  # a dictionary that associates to an edge an integer value (for instance, a cost)
        self.__addDefaultVertices(vertices)

    @property
    def edges_cost(self):
        return self._edges_cost

    @edges_cost.setter
    def edges_cost(self, other):
        self._edges_cost = other

    @property
    def vertices_in(self):
        return self._vertices_in

    @vertices_in.setter
    def vertices_in(self, other):
        self._vertices_in = other

    @property
    def vertices_out(self):
        return self._vertices_out

    @vertices_out.setter
    def vertices_out(self, other):
        self._vertices_out = other

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
        return len(self._vertices_out)

    def getEdgesNo(self):
        """
            Gets the number of edges of the graph
            :return: the number of edges of the graph
        """
        return len(self._edges_cost)

    def isEdge(self, edge_x, edge_y):
        """
            Tests if two vertices form an edge
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :return: true if the vertices form an edge, false else
            :raises: DirectedGraphException if the given vertices do not exist
        """
        if edge_x not in self._vertices_out.keys() or edge_y not in self._vertices_in.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        return edge_y in self._vertices_out[edge_x]

    def getInDegree(self, vertex):
        """
            Gets the in degree of a vertex
            :param vertex: a vertex of the graph
            :return: the in degree of a vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return len(self._vertices_in[vertex])

    def getOutDegree(self, vertex):
        """
            Gets the out degree of a vertex
            :param vertex: a vertex of the graph
            :return: the out degree of a vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return len(self._vertices_out[vertex])

    def parseVertices(self):
        """
            Parses the vertices of the graph
            :return: an iterator for parsing the vertices of the graph
        """
        return GraphIterator(list(self._vertices_out.keys()))

    def parseVerticesOut(self, vertex):
        """
            Parses the outbound neighbours of a given vertex
            :param vertex: a vertex of the graph
            :return: an iterator for parsing the outbound neighbours of a given vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return GraphIterator(self._vertices_out[vertex])

    def parseVerticesIn(self, vertex):
        """
            Parses the inbound neighbours of a given vertex
            :param vertex: a vertex of the graph
            :return: an iterator for parsing the inbound neighbours of a given vertex
            :raises: DirectedGraphException if the given vertex is not valid
        """
        if vertex not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertex.\n")
        return GraphIterator(self._vertices_in[vertex])

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
        return self._edges_cost[(edge_x, edge_y)]

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
        self._edges_cost[(edge_x, edge_y)] = cost

    def addEdge(self, edge_x, edge_y, cost):
        """
            Adds an edge to the graph
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :param cost: the cost of the edge
            :raises: DirectedGraphException if the vertices and/or the edge do not exist
        """
        if edge_x not in self._vertices_out.keys() or edge_y not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        if edge_y in self._vertices_out[edge_x]:
            raise DirectedGraphException("Edge already exists.\n")
        self._vertices_out[edge_x].append(edge_y)
        self._vertices_in[edge_y].append(edge_x)
        self._edges_cost[(edge_x, edge_y)] = cost

    def removeEdge(self, edge_x, edge_y):
        """
            Removes an edge of the graph
            :param edge_x: the start vertex of the edge
            :param edge_y: the end vertex of the edge
            :raises: DirectedGraphException if the vertices and/or the edge do not exist
        """
        if edge_x not in self._vertices_out.keys() or edge_y not in self._vertices_out.keys():
            raise DirectedGraphException("Invalid vertices.\n")
        if edge_y not in self._vertices_out[edge_x]:
            raise DirectedGraphException("Edge does not exist.\n")
        self._vertices_out[edge_x].remove(edge_y)
        self._vertices_in[edge_y].remove(edge_x)
        del self._edges_cost[(edge_x, edge_y)]

    def addVertex(self, vertex):
        """
            Adds a vertex to the graph
            :param vertex: the vertex to be added
            :raises: DirectedGraphException if the vertex does not exist
        """
        if vertex in self._vertices_out.keys():
            raise DirectedGraphException("The vertex was already added.\n")
        self._vertices_out[vertex] = []
        self._vertices_in[vertex] = []

    def removeVertex(self, vertex):
        """
            Removes a vertex of the graph
            :param vertex: the vertex to be removed
            :raises: DirectedGraphException if the vertex does not exist
        """
        if vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertex was not found.\n")
        for edge_y in self._vertices_out[vertex]:
            del self._edges_cost[(vertex, edge_y)]
            self._vertices_in[edge_y].remove(vertex)
        for edge_x in self._vertices_in[vertex]:
            del self._edges_cost[(edge_x, vertex)]
            self._vertices_out[edge_x].remove(vertex)
        del self._vertices_out[vertex]
        del self._vertices_in[vertex]

    def copyGraph(self):
        """
            Gets a copy of the graph
            :return: a copy of the graph
        """
        graph = DirectedGraph(self.getVerticesNo())
        graph._edges_cost = copy.deepcopy(self._edges_cost)
        for vertex in self.parseVertices():
            graph._vertices_in[vertex] = copy.deepcopy(self._vertices_in[vertex])
            graph._vertices_out[vertex] = copy.deepcopy(self._vertices_out[vertex])
        return graph

    def breadthFirstSearch(self, start_vertex, destination_vertex):
        """
        Performs a breadth first search in order to find the minimum length path between two given nodes
        :param start_vertex: the source node
        :param destination_vertex: the destination node
        :return: the minimum length to destination node and a list with the nodes in the path
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")

        distance = {}
        previous = {}
        visited = {}
        queue = SimpleQueue()

        distance[start_vertex] = 0
        visited[start_vertex] = True
        queue.put(start_vertex)

        searching = True
        while not queue.empty() and searching:
            current_node = queue.get()
            for neighbour in self.parseVerticesOut(current_node):
                if neighbour not in visited or not visited[neighbour]:
                    visited[neighbour] = True
                    distance[neighbour] = distance[current_node] + 1
                    previous[neighbour] = current_node
                    queue.put(neighbour)

                    if neighbour == destination_vertex:
                        searching = False
                        break

        if destination_vertex not in distance:
            raise DirectedGraphException(
                "There is no path from node {} to node {}!".format(start_vertex, destination_vertex))
        return distance[destination_vertex], self.__findBreadthFirstSearchPath(start_vertex, destination_vertex,
                                                                               previous)

    def __findBreadthFirstSearchPath(self, start_vertex, destination_vertex, previous):
        """
        Finds the minimum length path between two nodes
        :param start_vertex: the source node
        :param destination_vertex: the destination node
        :param previous: a dictionary mapping the nodes to their previous nodes in the found path
        :return: the found path
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")
        if start_vertex == destination_vertex:
            return [start_vertex]
        current_path = self.__findBreadthFirstSearchPath(start_vertex, previous[destination_vertex], previous)
        current_path.append(destination_vertex)
        return current_path

    def depthFirstSearch(self, start_vertex, visited, processed):
        """
        Depth first search algorithm for graph traversal
        :param start_vertex: the source node
        :param visited: the visited list of nodes
        :param processed: the processed list of nodes (acts like a stack)
        """
        if start_vertex in visited:
            return
        visited.append(start_vertex)

        for neighbour in self.parseVerticesOut(start_vertex):
            self.depthFirstSearch(neighbour, visited, processed)
        processed.append(start_vertex)

    def findStronglyConnectedComponents(self):
        """
        Finds the strongly connected components of the graph, using the Kosaraju Algorithm
        :return: a list of lists, each of them containing the nodes from a strongly connected component
        """
        processed = []
        visited = []
        components = []

        for node in self.parseVertices():
            if node not in visited:
                self.depthFirstSearch(node, visited, processed)

        visited = []
        queue = SimpleQueue()
        component_no = 0

        while len(processed):
            processed_node = processed.pop()
            if processed_node not in visited:
                component_no += 1
                components.append([processed_node])
                queue.put(processed_node)
                visited.append(processed_node)
                while not queue.empty():
                    current_node = queue.get()
                    for neighbour in self.parseVerticesIn(current_node):
                        if neighbour not in visited:
                            visited.append(neighbour)
                            queue.put(neighbour)
                            components[component_no - 1].append(neighbour)
        for index in range(component_no):
            components[index] = reversed(components[index])
        return components

    def findLowestCostWalkMatrixMultiplication(self, start_vertex, destination_vertex):
        """
        Finds the lowest cost walk between two vertices, using the Matrix Multiplication Algorithm
        Time Complexity: θ(n^3 * log_n)
        :param start_vertex: the start vertex
        :param destination_vertex: the destination vertex
        :return: a tuple consisting of the minimum distance that was found by the algorithm and the corresponding walk
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")

        costs = []
        nexts = []
        possibilities = []

        # consider an index for each node: the first one has index 0, the second one 1, ...
        for node_i in self.parseVertices():
            current_line = []
            current_nexts = []
            index = 0
            for node_j in self.parseVertices():
                current_line.append(math.inf)
                current_nexts.append(math.inf)
                if (node_i, node_j) in self._edges_cost:
                    current_line[-1] = self._edges_cost[(node_i, node_j)]
                if self.isEdge(node_i, node_j):
                    current_nexts[-1] = index
                elif node_i == node_j:
                    current_line[-1] = 0
                index += 1
            costs.append(current_line)
            nexts.append(current_nexts)

        result_matrix = self.__matrixMultiplicationAlgorithm(costs, self.getVerticesNo() - 1, nexts)
        # result_matrix = self.__matrixMultiplicationAlgorithmNotRec(costs, nexts)
        minimum_distance = result_matrix[start_vertex][destination_vertex]

        current = start_vertex
        path = []

        for node in self.parseVertices():
            if result_matrix[node][node] < 0:
                return None, None

        # compute the minimum cost path
        while current != math.inf:
            path.append(current)
            current = nexts[current][destination_vertex]
        return minimum_distance, path

    def __matrixMultiplicationAlgorithmNotRec(self, default_costs, nexts):
        """
        Finds the costs matrix ^(n-1), without using recursion. Hence, the time complexity is θ(n)
        :param default_costs: default costs matrix
        :param nexts: next[i][j] = k <=> k is the next node after i in the minimum cost walk from i to j
        :return: the costs matrix at "power" (n - 1)
        """
        costs = copy.deepcopy(default_costs)
        for power in range(2, self.getVerticesNo() - 1):
            costs = self.__matrixMultiplicationExtend(costs, default_costs, nexts)
        return costs

    def __matrixMultiplicationAlgorithm(self, default_costs, power, nexts):
        """
        Finds the costs matrix ^(power), using recursion. Hence, the time complexity is θ(log_n)
        :param default_costs: default costs matrix
        :param power: the current power of the matrix
        :param nexts: next[i][j] = k <=> k is the next node after i in the minimum cost walk from i to j
        :return: the costs matrix ^(power)
        """
        if power == 1:
            return default_costs
        matrix_log = self.__matrixMultiplicationAlgorithm(default_costs, power // 2, nexts)
        result = self.__matrixMultiplicationExtend(matrix_log, matrix_log, nexts)
        if power % 2 == 1:
            result = self.__matrixMultiplicationExtend(result, default_costs, nexts)
        return result

    def __matrixMultiplicationExtend(self, matrix_a, matrix_b, nexts):
        """
        Performs the "matrix multiplication" part of the algorithm
        :param matrix_a: the first matrix
        :param matrix_b: the second matrix
        :param nexts: the nexts list
        :return: the result of the "multiplication"
        """
        n = self.getVerticesNo()
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    if matrix_a[i][j] > matrix_a[i][k] + matrix_b[k][j]:
                        matrix_a[i][j] = matrix_a[i][k] + matrix_b[k][j]
                        nexts[i][j] = nexts[i][k]
        # print()
        # for l in matrix_a:
        #     print(l)
        # print()

        return matrix_a

    def findTotalNumberOfPaths(self, start_vertex, destination_vertex, counter=0):
        """
        Finds the total number of distinct walks between two vertices in a DAG
        :param start_vertex: the source vertex
        :param destination_vertex: the destination vertex
        :param counter: the counter
        :return: the found number of walks
        """
        if start_vertex == destination_vertex:
            counter += 1
        else:
            for neighbour in self.parseVerticesOut(start_vertex):
                counter = self.findTotalNumberOfPaths(neighbour, destination_vertex, counter)
        return counter

    def findTotalNumberOfPathsWithMinCost(self, start_vertex, destination_vertex, minimum_cost, visited=[], current_cost=0, counter=0):
        """
        Finds the total number of minimum cost walks between two vertices in a graph without negative cost cycles
        :param start_vertex: the source vertex
        :param destination_vertex: the destination vertex
        :param minimum_cost: the minimum cost between the two vertices
        :param visited: a list that contains the currently visited nodes
        :param current_cost: the cost of the current walk
        :param counter: the number of found walks
        :return: the number of found walks
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")
        if start_vertex in visited:
            return counter
        visited.append(start_vertex)

        if start_vertex == destination_vertex and current_cost == minimum_cost:
            counter += 1
        elif start_vertex == destination_vertex:
            return counter
        else:
            for neighbour in self.parseVerticesOut(start_vertex):
                counter = self.findTotalNumberOfPathsWithMinCost(neighbour, destination_vertex, minimum_cost, visited,
                                               current_cost + self.getCost(start_vertex, neighbour), counter)
                if neighbour in visited:
                    visited.remove(neighbour)
        return counter

    def topologicalSort(self):
        """
        Performs (or attempts to) a topological sorting on the graph
        """
        sorted_vertices = []
        queue = SimpleQueue()
        count = {}

        for node in self.parseVertices():
            count[node] = self.getInDegree(node)
            if not count[node]:
                queue.put(node)

        while not queue.empty():
            current_node = queue.get()
            sorted_vertices.append(current_node)
            for neighbour in self.parseVerticesOut(current_node):
                count[neighbour] -= 1
                if not count[neighbour]:
                    queue.put(neighbour)

        if len(sorted_vertices) < self.getVerticesNo():
            return None
        return sorted_vertices

    def findDistinctPathsNumber(self, start_vertex, destination_vertex):
        """
        Finds the number of distinct paths between two vertices
        """
        paths = {}  # paths[(i, j)] = the number of distinct paths between node i and node j
        for node in self.parseVertices():
            paths[(node, node)] = 1  # true because we assume the graph is a DAG
        return self.findDistinctPathsNumberRecursive(start_vertex, destination_vertex, paths)

    def findDistinctPathsNumberRecursive(self, start_vertex, destination_vertex, paths):
        """
        Recursive function used in finding the number of distinct paths between two vertices
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")

        paths_no = 0
        for node in self.parseVerticesOut(start_vertex):
            if (node, destination_vertex) not in paths:
                paths[(node, destination_vertex)] = self.findDistinctPathsNumberRecursive(node, destination_vertex, paths)
            paths_no += paths[(node, destination_vertex)]
        return paths_no

    def findDistinctLowestCostPathsNo(self, start_vertex, destination_vertex):
        """
        Finds the number of distinct lowest cost paths between two given vertices
        """
        if start_vertex not in self._vertices_out.keys() or destination_vertex not in self._vertices_out.keys():
            raise DirectedGraphException("The vertices were not found.\n")

        sorted_nodes = self.topologicalSort()
        found_start = False
        min_cost = {}
        paths_no = {}

        for node in sorted_nodes:
            min_cost[node] = math.inf
            paths_no[node] = 0

        min_cost[start_vertex] = 0
        paths_no[start_vertex] = 1

        for node in sorted_nodes:
            if not found_start and node == destination_vertex:
                return 0
            if node == start_vertex:
                found_start = True
                continue
            for in_node in self.parseVerticesIn(node):
                if min_cost[in_node] + self._edges_cost[(in_node, node)] < min_cost[node]:
                    min_cost[node] = min_cost[in_node] + self._edges_cost[(in_node, node)]
                    paths_no[node] = paths_no[in_node]
                elif min_cost[in_node] + self._edges_cost[(in_node, node)] == min_cost[node]:
                    paths_no[node] += paths_no[in_node]
        return min_cost[destination_vertex], paths_no[destination_vertex]
