import random

INF = 1000000000


class DirectedGraph:
    def __init__(self, n=3):
        self.__next_vertex_id = n  # no_vertices plus the number of removed vertices
        self.__no_vertices = n
        self.__m = 0

        self.__inbound_edges = dict()
        self.__outbound_edges = dict()
        self.__edge_costs = dict()  # (a,b)->cost
        for vertex in range(n):
            self.__inbound_edges[vertex] = list()
            self.__outbound_edges[vertex] = list()
        self.__vertex_was_removed = [False for _ in range(n)]

    def get_number_vertices(self):
        return self.__no_vertices

    def get_maximum_vertex_id(self):
        return self.__next_vertex_id - 1

    def get_number_edges(self):
        return self.__m

    def add_edge(self, vertex_a, vertex_b, cost):
        if not self.__exists_vertex(vertex_a) or not self.__exists_vertex(vertex_b):
            raise ValueError()
        if self.exists_edge(vertex_a, vertex_b):
            raise ValueError()

        self.__outbound_edges[vertex_a].append(vertex_b)
        self.__inbound_edges[vertex_b].append(vertex_a)
        self.__edge_costs[(vertex_a, vertex_b)] = cost
        self.__m += 1

    def parse_vertices(self):
        vertices = []
        for i in range(self.__next_vertex_id):
            if not self.__vertex_was_removed[i]:
                vertices.append(i)
        return vertices

    def __exists_vertex(self, vertex):
        return 0 <= vertex < self.__next_vertex_id and not self.__vertex_was_removed[vertex]

    def exists_edge(self, a, b):
        if not self.__exists_vertex(a) or not self.__exists_vertex(b):
            raise ValueError()

        for vertex in self.__outbound_edges[a]:
            if vertex == b:
                return True
        return False

    def get_in_degree(self, vertex):
        if not self.__exists_vertex(vertex):
            raise ValueError()
        return len(self.__inbound_edges[vertex])

    def get_out_degree(self, vertex):
        if not self.__exists_vertex(vertex):
            raise ValueError()
        return len(self.__outbound_edges[vertex])

    def parse_outbound_edges(self, vertex):
        if not self.__exists_vertex(vertex):
            raise ValueError()
        return list(self.__outbound_edges[vertex])

    def parse_inbound_edges(self, vertex):
        if not self.__exists_vertex(vertex):
            raise ValueError()
        return list(self.__inbound_edges[vertex])

    def get_edge_cost(self, a, b):
        """
        We assume there is just one edge from a to b
        """
        if not self.__exists_vertex(a) or not self.__exists_vertex(b):
            raise ValueError()
        if b not in self.__outbound_edges[a]:
            return None
        return self.__edge_costs[(a, b)]

    def set_edge_cost(self, a, b, new_cost):
        """
        We assume there is just one edge from a to b
        """
        if not self.__exists_vertex(a) or not self.__exists_vertex(b):
            raise ValueError()
        if b not in self.__outbound_edges[a]:
            return ValueError()
        self.__edge_costs[(a, b)] = new_cost

    def make_it_equal_to(self, new_graph):
        """
        Given another graph, make "self" equal to that graph
        """
        self.__next_vertex_id = new_graph.get_maximum_vertex_id() + 1
        self.__m = new_graph.get_number_edges()
        self.__no_vertices = new_graph.get_number_vertices()

        self.__outbound_edges = dict()
        self.__inbound_edges = dict()
        for vertex in new_graph.parse_vertices():
            self.__outbound_edges[vertex] = list()
            self.__inbound_edges[vertex] = list()
        self.__vertex_was_removed = [True for _ in range(self.__next_vertex_id)]
        self.__edge_costs = dict()
        for vertex in new_graph.parse_vertices():
            self.__vertex_was_removed[vertex] = False
            their_outbound = new_graph.parse_outbound_edges(vertex)
            for neighbor in their_outbound:
                cost = new_graph.get_edge_cost(vertex, neighbor)
                self.__outbound_edges[vertex].append(neighbor)
                self.__inbound_edges[neighbor].append(vertex)
                self.__edge_costs[vertex, neighbor] = cost


def load_graph_from_file(filename):
    fin = open(filename, "r")
    line = fin.readline()
    n = int(line.split()[0])
    m = int(line.split()[1])
    read_graph = DirectedGraph(n)

    for i in range(m):
        line = fin.readline()
        vertex_a, vertex_b, cost = int(line.split()[0]), int(line.split()[1]), int(line.split()[2])
        read_graph.add_edge(vertex_a, vertex_b, cost)
    fin.close()

    return read_graph


def write_graph_to_file(graph: DirectedGraph, filename):
    fout = open(filename, "w")
    fout.write(str(graph.get_number_vertices()) + " " + str(graph.get_number_edges()) + "\n")
    for vertex in graph.parse_vertices():
        for edge_vertex in graph.parse_outbound_edges(vertex):
            cost = graph.get_edge_cost(vertex, edge_vertex)
            fout.write(str(vertex) + " " + str(edge_vertex) + " " + str(cost) + "\n")
    fout.close()


def generate_random_graph(no_vertices, no_edges) -> DirectedGraph:
    graph = DirectedGraph(no_vertices)
    for _ in range(no_edges):
        a = random.randint(0, no_vertices - 1)
        b = random.randint(0, no_vertices - 1)
        while graph.exists_edge(a, b):
            a = random.randint(0, no_vertices - 1)
            b = random.randint(0, no_vertices - 1)
        cost = random.randint(-20, 20)

        graph.add_edge(a, b, cost)
    return graph


def cost_of_walk(graph, walk):
    """ Given a directed graph and a walk, returns the cost of the walk.

    :param graph: graph of any class which has method "get_edge_cost"
    :param walk: list with the vertices (must be passable as arguments to get_edge_cost)
    :return: the cost of the walk (int)
    """
    total_cost = 0
    for idx in range(0, len(walk) - 1):
        cost_here = graph.get_edge_cost(walk[idx], walk[idx + 1])
        total_cost += cost_here
    return total_cost


def count_lowest_cost_paths_in_dag(graph: DirectedGraph, topological_order, vertex_source, vertex_dest):
    """
    Given a DAG and two vertices, returns how many min cost walks exist between them.

    :param graph: DirectedGraph which is a DAG
    :param topological_order: "graph"'s vertices, in topological order
    :param vertex_source: valid vertex ID in "graph"
    :param vertex_dest:  valid vertex ID in "graph"
    :return: the number of min cost walks between the vertices (int)
    """
    # a vertex which is on a path from "a" to "b" is between them in the topological order
    # algorithm: take the vertices in order, and for each vertex, look at its inbound neighbors
    # to first compute the distance, and then the number of minimum cost walk

    distance_from_source = dict()  # vertex->distance from "source" to it
    no_walks_from_source = dict()  # vertex->no. of walks from "source" to it
    found_the_source = False
    for vertex in topological_order:
        if vertex == vertex_source:
            found_the_source = True
            distance_from_source[vertex] = 0
            no_walks_from_source[vertex] = 1
        else:
            if not found_the_source:  # if it's before the "source", no path
                distance_from_source[vertex] = INF
                no_walks_from_source[vertex] = 0
            else:
                # look at inbound neighbors
                distance_from_source[vertex] = INF  # first get the distance
                for neighbor in graph.parse_inbound_edges(vertex):
                    distance_from_source[vertex] = min(distance_from_source[vertex], distance_from_source[neighbor] + graph.get_edge_cost(neighbor, vertex))
                no_walks_from_source[vertex] = 0  # then the number of walks
                for neighbor in graph.parse_inbound_edges(vertex):
                    if distance_from_source[neighbor] + graph.get_edge_cost(neighbor, vertex) == distance_from_source[vertex]:
                        no_walks_from_source[vertex] += no_walks_from_source[neighbor]
                if vertex == vertex_dest:
                    break
    return no_walks_from_source[vertex_dest]


def count_walks_in_dag_till_vertex_recursively(graph: DirectedGraph, vertex_source, vertex_current,
                                               results_till_now: dict):
    """
    Given a DAG and two vertices, returns how many walks there are from the first vertex
    to the second one, by doing a recursive call.

    :param graph: DirectedGraph which is acyclic
    :param vertex_source: the ID of the vertex from which we do the walk
    :param vertex_current: the ID of the vertex to which we do the walk
    :param results_till_now: memoization based on "vertex_current" (dict vertex->result)
    :param: how many walks from "vertex_source" to "vertex_current"
    """

    if vertex_current == vertex_source:
        return 1
    if vertex_source in results_till_now:  # memoization
        return results_till_now[vertex_source]

    # dynamic programming: for each vertex going into "vertex_current", all walks reaching there
    # are valid walks to "vertex_current", and all "current"'s neighbors give disjoint sets of walks
    # (because there are no cycles)
    walks_total = 0
    for neighbor in graph.parse_inbound_edges(vertex_current):
        walks_total += count_walks_in_dag_till_vertex_recursively(graph, vertex_source, neighbor, results_till_now)
    results_till_now[vertex_current] = walks_total
    return walks_total


def count_paths_in_dag(graph: DirectedGraph, vertex_source, vertex_dest):
    """ Given a directed acyclic graph and two vertices, returns how many walks
    exist from the first to the second one.

    :param graph: DirectedGraph
    :param vertex_source: valid vertex ID in "graph"
    :param vertex_dest: valid vertex ID in "graph"
    :return: the number of walks from "vertex_source" to "vertex_dest"
    """
    return count_walks_in_dag_till_vertex_recursively(graph, vertex_source, vertex_dest, dict())


def get_topological_order(graph: DirectedGraph):
    """ Given a directed graph, returns their vertices sorted topologically.

    :param graph: DirectedGraph object
    :return: list with the vertices in topological order, if "graph" is a DAG; -1 otherwise
    """
    vertices_queue = []
    new_in_degree = dict()  # in degree if we don't take in consideration vertices which we added to the order
    for vertex in graph.parse_vertices():
        if graph.get_in_degree(vertex) == 0:
            vertices_queue.append(vertex)
        else:
            new_in_degree[vertex] = graph.get_in_degree(vertex)

    the_order = []
    while len(vertices_queue) > 0:
        current = vertices_queue.pop(0)
        the_order.append(current)
        for neighbor in graph.parse_outbound_edges(current):
            new_in_degree[neighbor] -= 1
            if new_in_degree[neighbor] == 0:
                vertices_queue.append(neighbor)

    if len(the_order) < graph.get_number_vertices():
        return -1  # not a DAG
    return the_order
