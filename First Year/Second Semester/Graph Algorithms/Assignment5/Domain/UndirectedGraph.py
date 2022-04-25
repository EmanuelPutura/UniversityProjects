from random import randint

from Domain.DirectedGraph import DirectedGraph


class UndirectedGraph(DirectedGraph):
    """
    UndirectedGraph class, represents an undirected graph
    """
    def __init__(self, vertices=0):
        super().__init__(vertices)

    def addEdge(self, edge_x, edge_y, cost):
        """
        Adds an edge to the graph
        :param edge_x: the edge source vertex
        :param edge_y: the edge destination vertex
        :param cost: the cost of the edge
        """
        super().addEdge(edge_x, edge_y, cost)
        super().vertices_out[edge_y].append(edge_x)
        super().vertices_in[edge_x].append(edge_y)

    def removeEdge(self, edge_x, edge_y):
        pass

    def removeVertex(self, vertex):
        pass

    def findBiconnectedComponents(self, visited, lowpoint, stack, component):
        """
        Makes use of Tarjan's Algorithm to find the biconnected components in an unidrected graph
        """
        connected_comp = 0
        level = {}
        for node in self.parseVertices():
            if node not in visited:
                connected_comp += 1
                level[node] = 0
                self.findBiconnectedComponentsDFS(node, node, visited, level, lowpoint, stack, component)
        return connected_comp

    def findBiconnectedComponentsDFS(self, start, parent, visited, level, lowpoint, stack, component):
        """
        Tarjan's Algorithm for finding biconnected components of an undirected graph
        :param start: the start node
        :param parent: the parent node
        :param visited: the visited list
        :param level: the level dict
        :param lowpoint: the lowpoint dict
        :param stack: the processing stack
        :param component: the components list
        """
        visited.append(start)
        stack.append(start)
        level[start] = level[parent] + 1
        lowpoint[start] = level[start]

        for neighbour in self.parseVerticesOut(start):
            if neighbour != parent:
                if neighbour in visited:
                    if lowpoint[start] > level[neighbour]:
                        lowpoint[start] = level[neighbour]
                else:
                    self.findBiconnectedComponentsDFS(neighbour, start, visited, level, lowpoint, stack, component)
                    if lowpoint[start] > lowpoint[neighbour]:
                        lowpoint[start] = lowpoint[neighbour]

                    if level[start] <= lowpoint[neighbour]:
                        component.append([])
                        while stack[-1] != neighbour:
                            component[-1].append(stack[-1])
                            stack.pop()
                        component[-1].append(neighbour)
                        stack.pop()
                        component[-1].append(start)

    def constructMinimalSpanningTree(self):
        """
        Constructs a minimal spanning tree using the Kruskal's Algorithm
        :return: a list consisting of the edges of the found minimal spanning tree
        """
        edges = []
        for edge in self._edges_cost:
            edges.append((edge[0], edge[1], self.edges_cost[edge]))
        edges.sort(key=lambda element: element[2])  # sort the edges of the graph by cost

        found_edges = []  # found edges in the minimum spanning tree
        link = {}         # link[node] = p <=> p is the parent of node in its current component
        height = {}       # height[node] = s <=> the height of the current component tree is s

        for vertex in self.parseVertices():
            link[vertex] = vertex
            height[vertex] = 1

        for edge in edges:
            if not self.__sameComponentKruskal(edge[0], edge[1], link):
                self.__uniteComponentsKruskal(edge[0], edge[1], link, height)
                found_edges.append(edge)
        return found_edges

    def __findComponentKruskal(self, node, link):
        """
        Finds the parent of a component. Used for implementing Kruskal's Algorithm
        """
        while node != link[node]:
            node = link[node]
        return node

    def __findComponentAndCompress(self, node, link):
        """
        Finds the parent of a component and compresses the path to it by making all the vertices along the path direct children of the parent
        Used for implementing Kruskal's Algorithm
        """
        if link[node] == node:
            return node
        parent = self.__findComponentAndCompress(link[node], link)
        link[node] = parent
        return parent

    def __sameComponentKruskal(self, node1, node2, link):
        """
        Checks if two nodes are in the same component. Used for implementing Kruskal's Algorithm
        """
        return self.__findComponentAndCompress(node1, link) == self.__findComponentAndCompress(node2, link)

    def __uniteComponentsKruskal(self, node1, node2, link, height):
        """
        Unifies two components. Used for implementing Kruskal's Algorithm
        """
        parent1 = self.__findComponentAndCompress(node1, link)
        parent2 = self.__findComponentAndCompress(node2, link)
        if height[parent1] < height[parent2]:
            parent1, parent2 = parent2, parent1

        height[parent1] += height[parent2]
        link[parent2] = parent1

    def findMinimumVertexCoverBS(self):
        """
        Finds the minimum vertex cover in a graph, using a binary search based algorithm (and a Gosper’s result)
        """
        left = 1
        right = self.getVerticesNo()
        vertices = []
        return_vertices = []

        while right > left:
            middle = (left + right) >> 1
            vertices = self.existsVertexCover(middle)
            if vertices is None:
                left = middle + 1
            else:
                right = middle
                return_vertices = vertices
        return return_vertices

    def existsVertexCover(self, size):
        """
        Checks if there exists a vertex cover of the given size
        """
        bits_set = (1 << size) - 1
        limit = (1 << self.getVerticesNo())

        covered_edges = {}
        vertices = []
        all_vertices = list(self._vertices_out)

        # the selected vertices are the ones having the indices corresponding to the 1s of the bits set
        while bits_set < limit:
            covered_edges = {}
            vertices = []

            count = 0
            current_position = 1
            current_vertex_index = 0
            while current_position < limit:
                if bits_set & current_position:
                    # mark all edges emerging out of the current vertex
                    current_vertex = all_vertices[current_vertex_index]
                    vertices.append(current_vertex)

                    for neighbour in self.parseVerticesOut(current_vertex):
                        if (current_vertex, neighbour) not in covered_edges:
                            covered_edges[(current_vertex, neighbour)] = covered_edges[(neighbour, current_vertex)] = True
                            count += 1
                current_position = current_position << 1
                current_vertex_index += 1
            if count == self.getEdgesNo():
                return vertices

            c = bits_set & -bits_set
            r = bits_set + c
            bits_set = (((r ^ bits_set) >> 2) // c) | r
        return None

    def findMinimumVertexCoverGreedy(self):
        """
        Finds the minimum vertex cover in a graph, using a greedy based algorithm
        """
        sorted_vertices = list(self._vertices_out)  # the list of vertices sorted by out(in) degree
        sorted_vertices.sort(key=lambda element: len(self.vertices_out[element]))
        covered_edges = []  # the covered edges so far

        selected_vertices = []
        count_nodes = 1
        count_edges = 0

        while count_edges != self.getEdgesNo():
            current_vertex = sorted_vertices[-count_nodes]
            count_nodes += 1

            selected_vertices.append(current_vertex)
            for neighbour in self.parseVerticesOut(current_vertex):
                if (current_vertex, neighbour) not in covered_edges:
                    covered_edges.append((current_vertex, neighbour))
                    covered_edges.append((neighbour, current_vertex))
                    count_edges += 1
        return selected_vertices

    def findMinimumVertexCoverApproximation(self):
        """
        Finds the minimum vertex cover in a graph, using an approximation algorithm
        """
        edges = []
        for edge in self._edges_cost:
            edges.append((edge[0], edge[1]))
        result = []

        for vertex in self.parseVertices():
            if vertex not in result:
                for neighbour in self.parseVerticesOut(vertex):
                    if neighbour not in result:
                        result.append(vertex)
                        result.append(neighbour)
                        break
        return result
