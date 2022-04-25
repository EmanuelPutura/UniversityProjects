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
