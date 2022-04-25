from random import randint, shuffle
from Domain.DirectedGraph import DirectedGraph


class GraphRandomGenerator:
    @staticmethod
    def generateGraph(vertices, edges):
        """
            Generates a random graph
            :param vertices: number of vertices for the generated graph
            :param edges: number of edges for the generated graph
            :return: the generated graph
            :raises: ValueError if the graph cannot be generated
        """
        if edges > vertices * vertices:
            raise ValueError("Invalid number of edges (too many).\n")

        all_edges = []
        for x in range(vertices):
            for y in range(vertices):
                cost = randint(0, 100)
                all_edges.append((x, y, cost))
        shuffle(all_edges)

        graph = DirectedGraph(vertices)
        for i in range(edges):
            graph.addEdge(all_edges[i][0], all_edges[i][1], all_edges[i][2])
        return graph
