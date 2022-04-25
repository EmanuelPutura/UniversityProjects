from Domain.UndirectedGraph import UndirectedGraph
from Domain.DirectedGraph import DirectedGraph, DirectedGraphException
from FileManager.FileManager import FileManager
from GraphGenerator.GraphRandomGenerator import GraphRandomGenerator


class ConsoleUI:
    def __init__(self):
        self.__directed_graph = DirectedGraph()
        self.__commands = {"1": self.__createRandomGraph, "2": self.__readGraphFromTextFile, "3": self.writeGraphToTextFile, "4": self.getVerticesNo,
                           "5": self.displayAllVertices, "6": self.testEdge, "7": self.displayInOutDegree, "8": self.displayOutboundEdges, "9": self.displayInboundEdges,
                           "10": self.getCost, "11": self.setCost, "12": self.addEdge, "13": self.removeEdge, "14": self.addVertex, "15": self.removeVertex,
                           "16": self.findLowestLengthPathBFS, "17": self.findStronglyConnectedComponents, "18": self.findBiconnectedComponents}

    def __createRandomGraph(self):
        vertices = input("Please input the number of vertices of the graph: ")
        edges = input("Please input the number of edges of the graph: ")

        try:
            self.__directed_graph = GraphRandomGenerator().generateGraph(int(vertices), int(edges))
        except ValueError as valueError:
            print(valueError)
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)
        except Exception as exception:
            print(exception)

    def __readGraphFromTextFile(self):
        file_path = "Files/"
        file_path += input("Please input the name of the input file: ")
        try:
            self.__directed_graph = FileManager().read(file_path)
        except FileNotFoundError as fileNotFoundError:
            print(fileNotFoundError)
        except Exception as exception:
            print(exception)

    def writeGraphToTextFile(self):
        file_path = "Files/"
        file_path += input("Please input the name of the output file: ")
        try:
            FileManager().write(self.__directed_graph, file_path)
        except Exception as exception:
            print(exception)

    def getVerticesNo(self):
        vertices_no = self.__directed_graph.getVerticesNo()
        print("There are {} vertices in the graph.\n".format(str(vertices_no)))

    def displayAllVertices(self):
        print("The vertices of the graph are:")
        vertices_str = ""
        for vertex in self.__directed_graph.parseVertices():
            vertices_str += (str(vertex) + ", ")
        vertices_str = vertices_str[:-2]
        print(vertices_str)

    def testEdge(self):
        edge_x = input("Please input the source vertex: ")
        edge_y = input("Please input the destination vertex: ")
        try:
            message = "form" if self.__directed_graph.isEdge(int(edge_x), int(edge_y)) else "do not form"
            print("The two vertices " + message + " an edge.")
        except Exception as exception:
            print(exception)

    def displayInOutDegree(self):
        vertex = input("Please input a vertex: ")
        try:
            in_degree = self.__directed_graph.getInDegree(int(vertex))
            out_degree = self.__directed_graph.getOutDegree(int(vertex))
            print("The in degree of the given vertex is {}.".format(in_degree))
            print("The out degree of the given vertex is {}.".format(out_degree))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)
        except Exception as exception:
            print(exception)

    def displayOutboundEdges(self):
        try:
            vertex = int(input("Please input a vertex: "))
        except Exception as exception:
            print(exception)
            return
        print("The outbound edges of the vertex {} are:".format(vertex))
        try:
            for edge_y in self.__directed_graph.parseVerticesOut(vertex):
                print("({}, {})".format(vertex, edge_y))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def displayInboundEdges(self):
        try:
            vertex = int(input("Please input a vertex: "))
        except Exception as exception:
            print(exception)
            return
        print("The inbound edges of the vertex {} is:".format(vertex))
        try:
            for edge_x in self.__directed_graph.parseVerticesIn(vertex):
                print("({}, {})".format(edge_x, vertex))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def getCost(self):
        try:
            edge_x = int(input("Please input the source vertex of the edge: "))
            edge_y = int(input("Please input the destination vertex of the edge: "))
        except Exception as exception:
            print(exception)
            return
        try:
            cost = self.__directed_graph.getCost(edge_x, edge_y)
            print("The cost associated to the edge ({}, {}) is {}.".format(edge_x, edge_y, cost))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def setCost(self):
        try:
            edge_x = int(input("Please input the source vertex of the edge: "))
            edge_y = int(input("Please input the destination vertex of the edge: "))
            cost = int(input("Please input the cost associated to the edge: "))
        except Exception as exception:
            print(exception)
            return
        try:
            self.__directed_graph.setCost(edge_x, edge_y, cost)
            print("The cost of the edge ({}, {}) was updated.".format(edge_x, edge_y))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def addEdge(self):
        try:
            edge_x = int(input("Please input the source vertex of the edge: "))
            edge_y = int(input("Please input the destination vertex of the edge: "))
            cost = int(input("Please input the cost associated to the edge: "))
        except Exception as exception:
            print(exception)
            return
        try:
            self.__directed_graph.addEdge(edge_x, edge_y, cost)
            print("The edge ({}, {}) was added.".format(edge_x, edge_y))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def removeEdge(self):
        try:
            edge_x = int(input("Please input the source vertex of the edge: "))
            edge_y = int(input("Please input the destination vertex of the edge: "))
        except Exception as exception:
            print(exception)
            return
        try:
            self.__directed_graph.removeEdge(edge_x, edge_y)
            print("The edge ({}, {}) was removed.".format(edge_x, edge_y))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def addVertex(self):
        try:
            vertex = int(input("Please input a vertex: "))
        except Exception as exception:
            print(exception)
            return
        try:
            self.__directed_graph.addVertex(vertex)
            print("The vertex {} was added.".format(vertex))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def removeVertex(self):
        try:
            vertex = int(input("Please input a vertex: "))
        except Exception as exception:
            print(exception)
            return
        try:
            self.__directed_graph.removeVertex(vertex)
            print("The vertex {} was removed.".format(vertex))
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def findLowestLengthPathBFS(self):
        try:
            source = int(input("Please input a source vertex: "))
            destination = int(input("Please input a destination vertex: "))
        except Exception as exception:
            print(exception)
            return
        try:
            distance, path = self.__directed_graph.breadthFirstSearch(source, destination)
            print("The length of the found path is: {}".format(distance))
            path_str = "The lowest length path is: "
            for node in path:
                path_str += "{} -> ".format(node)
            path_str = path_str[:-4]
            print(path_str)
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def findStronglyConnectedComponents(self):
        try:
            components = self.__directed_graph.findStronglyConnectedComponents()
            index = 1
            print("The graph has {} strongly connected components:".format(len(components)))

            for component in components:
                comp_str = "The strongly connected component no. {} is: ".format(index)
                for node in component:
                    comp_str += "{} -> ".format(node)
                comp_str = comp_str[:-4]
                print(comp_str)
                index += 1
        except DirectedGraphException as directedGraphException:
            print(directedGraphException)

    def findBiconnectedComponents(self):
        file_path = "Files/"
        print("An undirected graph must be loaded from an input file.")
        file_path += input("Please input the name of the input file: ")
        try:
            graph = FileManager().read(file_path, UndirectedGraph)
        except FileNotFoundError as fileNotFoundError:
            print(fileNotFoundError)
            return
        except Exception as exception:
            print(exception)
            return

        components = []

        components_no = graph.findBiconnectedComponents([], {}, [], components)
        if components_no > 1:
            print("\nNote that there are {} connected components in the graph".format(components_no))
        index = 1
        print("\nThe number of biconnected components is {}.".format(len(components)))
        for component in components:
            print("Biconnected component no. {} is: ".format(index))
            string = ""
            for node in component:
                string += "{} -> ".format(node)
            string = string[:-3]
            print(string)
            index += 1

    def __menu(self):
        print("\n" + "-" * 27 + " Graph Algorithms Assignment 1 Menu " + "-" * 27)
        print(" 1 - create a new random graph\n 2 - read a graph from a text file\n 3 - write the graph to a text file\n 4 - get the number of vertices in the graph")
        print(" 5 - display all the vertices in the graph\n 6 - test if there is an edge between two vertices\n 7 - display the in/out degree of a vertex")
        print(" 8 - display the outbound edges of a vertex\n 9 - display the inbound edges of a vertex\n10 - get cost of an edge\n11 - set cost of an edge")
        print("12 - add an edge\n13 - remove an edge\n14 - add a vertex\n15 - remove a vertex\n16 - given two vertices, finds a lowest length path between them, by using", end=" ")
        print("a forward breadth-first search from the starting vertex\n17 - find the strongly-connected components of the directed graph")
        print("18 - find the biconnected components of an undirected graph\n19 - exit the application")
        print("-" * 90)

    def run(self):
        running = True
        while running:
            try:
                self.__menu()
                command = input("command > ").strip()
                if command == "19":
                    running = False
                    break
                if command in self.__commands:
                    self.__commands[command]()
                else:
                    print("Invalid command.\n")
            except DirectedGraphException as directedGraphException:
                print("DirectedGraphException: " + str(directedGraphException))
            except Exception as exception:
                print("Unexpected exception occurred: " + str(exception))
