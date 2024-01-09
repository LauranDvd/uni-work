import random


class UndirectedGraph:
    def __init__(self, n=3):
        self.__next_vertex_id = n  # no_vertices, but includes the removed vertices
        self.__no_vertices = n
        self.__no_edges = 0

        self.__edges = dict()
        self.__edge_costs = dict()  # (a,b)->cost
        for vertex in range(n):
            self.__edges[vertex] = list()
        self.__vertex_was_removed = [False for _ in range(n)]

    def get_number_vertices(self):
        return self.__no_vertices

    def get_maximum_vertex_id(self):
        return self.__next_vertex_id - 1

    def get_number_edges(self):
        return self.__no_edges

    def add_edge(self, vertex_a, vertex_b, cost):
        if vertex_a not in self.parse_vertices() or vertex_b not in self.parse_vertices():
            raise ValueError()
        if self.exists_edge(vertex_a, vertex_b):
            raise ValueError()

        self.__edges[vertex_a].append(vertex_b)
        self.__edges[vertex_b].append(vertex_a)
        self.__edge_costs[(vertex_a, vertex_b)] = cost
        self.__edge_costs[(vertex_b, vertex_a)] = cost
        self.__no_edges += 1

    def parse_vertices(self):
        vertices = []
        for i in range(self.__next_vertex_id):
            if not self.__vertex_was_removed[i]:
                vertices.append(i)
        return vertices

    def exists_edge(self, a, b):
        if a not in self.parse_vertices() or b not in self.parse_vertices():
            raise ValueError()
        return b in self.__edges[a]

    def get_degree(self, vertex):
        if vertex not in self.parse_vertices():
            raise ValueError()
        return len(self.__edges[vertex])

    def parse_edges(self, vertex):
        if vertex not in self.parse_vertices():
            raise ValueError()
        return list(self.__edges[vertex])

    def get_edge_cost(self, a, b):
        """
        We assume there is just one edge from a to b
        """
        if a not in self.parse_vertices() or b not in self.parse_vertices():
            raise ValueError()
        if b not in self.__edges[a]:
            return None
        return self.__edge_costs[(a, b)]

    def set_edge_cost(self, a, b, new_cost):
        """
        We assume there is just one edge from a to b
        """
        if a not in self.parse_vertices() or b not in self.parse_vertices():
            raise ValueError()
        if b not in self.__edges[a]:
            return ValueError()
        self.__edge_costs[(a, b)] = new_cost
        self.__edge_costs[(b, a)] = new_cost

    def remove_vertex(self, vertex):
        if vertex not in self.parse_vertices():
            raise ValueError()

        count_edges = len(self.parse_edges(vertex))
        for neighbor in self.parse_edges(vertex):
            self.__edges[neighbor].remove(vertex)
            del self.__edge_costs[(vertex, neighbor)]
            del self.__edge_costs[(neighbor, vertex)]
        self.__edges[vertex] = []

        self.__no_vertices -= 1
        self.__no_edges -= count_edges
        self.__vertex_was_removed[vertex] = True

    def make_it_equal_to(self, new_graph):
        """
        Given another graph, make "self" equal to that graph
        """
        self.__next_vertex_id = new_graph.get_maximum_vertex_id() + 1
        self.__no_edges = new_graph.get_number_edges()
        self.__no_vertices = new_graph.get_number_vertices()

        self.__edges = dict()
        for vertex in new_graph.parse_vertices():
            self.__edges[vertex] = list()
        self.__vertex_was_removed = [True for _ in range(self.__next_vertex_id)]
        self.__edge_costs = dict()

        for vertex in new_graph.parse_vertices():
            self.__vertex_was_removed[vertex] = False
            for neighbor in new_graph.parse_edges(vertex):
                # it gets here in both ways
                cost = new_graph.get_edge_cost(vertex, neighbor)
                self.__edges[vertex].append(neighbor)
                self.__edge_costs[vertex, neighbor] = cost


def load_graph_from_file(graph: UndirectedGraph, filename):
    """
    Reads from a given file and saves in a given object a graph (class UndirectedGraph)
    """
    input_file = open(filename, "r")
    line = input_file.readline()
    no_vertices = int(line.split()[0])
    no_edges = int(line.split()[1])
    new_graph = UndirectedGraph(no_vertices)

    for i in range(no_edges):
        line = input_file.readline()
        vertex_a, vertex_b, cost = int(line.split()[0]), int(line.split()[1]), int(line.split()[2])
        new_graph.add_edge(vertex_a, vertex_b, cost)
    input_file.close()

    graph.make_it_equal_to(new_graph)


def write_graph_to_file(graph: UndirectedGraph, filename):
    output_file = open(filename, "w")
    written_edges = []  # pairs of vertices
    output_file.write(str(graph.get_number_vertices()) + " " + str(graph.get_number_edges()) + "\n")
    for vertex in graph.parse_vertices():
        for edge_vertex in graph.parse_edges(vertex):
            if (vertex, edge_vertex) not in written_edges and \
                    (edge_vertex, vertex) not in written_edges:  # only write an edge once
                cost = graph.get_edge_cost(vertex, edge_vertex)
                output_file.write(str(vertex) + " " + str(edge_vertex) + " " + str(cost) + "\n")
                written_edges.append((vertex, edge_vertex))
    output_file.close()


def generate_random_graph(no_vertices, no_edges) -> UndirectedGraph:
    graph = UndirectedGraph(no_vertices)
    for _ in range(no_edges):
        first_vertex = random.randint(0, no_vertices - 1)
        second_vertex = random.randint(0, no_vertices - 1)
        while graph.exists_edge(first_vertex, second_vertex):
            first_vertex = random.randint(0, no_vertices - 1)
            second_vertex = random.randint(0, no_vertices - 1)
        cost = random.randint(-20, 20)

        graph.add_edge(first_vertex, second_vertex, cost)
    return graph


def get_subgraph(graph: UndirectedGraph, vertices_to_keep):
    """
    Given a graph and which vertices to keep, return the corresponding subgraph

    :param graph: the UndirectedGraph
    :param vertices_to_keep: list with the ID's of the vertices (ints)
    :return: the subgraph (UndirectedGraph object)
    """
    subgraph = UndirectedGraph()
    subgraph.make_it_equal_to(graph)  # start from the original graph
    for vertex in graph.parse_vertices():
        if vertex not in vertices_to_keep:  # and remove the vertices which shouldn't be kept
            subgraph.remove_vertex(vertex)
    return subgraph


def depth_first_traversal(graph: UndirectedGraph, vertex, component_of_vertex: list, vertices_in_component: dict):
    """ Given a graph and a starting vertex, does a depth-first traversal on it while putting
    the visited vertices in the component which the starting vertex is already part of

    :param graph: the graph to traverse
    :param vertex: the starting point
    :param component_of_vertex: list, where the int at index k is the component of vertex k
    :param vertices_in_component: dict with a component (int) as key, and a list with its vertices as value
    """
    current_component = component_of_vertex[vertex]  # we fill all accessible vertices with current_component
    for neighbor in graph.parse_edges(vertex):
        if component_of_vertex[neighbor] == -1:  # unvisited yet
            component_of_vertex[neighbor] = current_component
            vertices_in_component[current_component].append(neighbor)
            depth_first_traversal(graph, neighbor, component_of_vertex, vertices_in_component)


def get_connected_components(graph: UndirectedGraph):
    """
    Finds the connected components of an undirected graph

    :param graph: the graph whose components will be found (UndirectedGraph object)
    :return: list of graphs--each a subgraph of "graph"--, one for each component (list of UndirectedGraph objects)
    """
    no_components = 0
    component_of_vertex = [-1] * (graph.get_maximum_vertex_id() + 1)
    vertices_in_component = dict()  # component_id -> list of vertices
    for vertex in graph.parse_vertices():
        if component_of_vertex[vertex] == -1:
            no_components += 1

            component_of_vertex[vertex] = no_components
            vertices_in_component[no_components] = [vertex]

            depth_first_traversal(graph, vertex, component_of_vertex, vertices_in_component)

    # print each component
    # for nr in range(1, no_components + 1):
    #     print("Component", nr)
    #     for node in graph.parse_vertices():
    #         if component_of_vertex[node] == nr:
    #             print(node)
    #     print("...")

    components_as_subgraphs = list()
    for component in range(1, no_components + 1):
        subgraph = get_subgraph(graph, vertices_in_component[component])
        components_as_subgraphs.append(subgraph)

    return components_as_subgraphs


def get_root(vertex, ancestor: dict):
    if ancestor[vertex] == vertex:
        return vertex
    the_root = get_root(ancestor[vertex], ancestor)
    ancestor[vertex] = the_root
    return the_root


def unite_trees(parent_one, parent_two, ancestor: dict, tree_size: dict):
    small_parent = parent_one  # attach the smaller tree to the larger one
    large_parent = parent_two
    if tree_size[parent_one] > tree_size[parent_two]:
        small_parent, large_parent = large_parent, small_parent

    ancestor[small_parent] = large_parent
    tree_size[large_parent] += tree_size[small_parent]
    tree_size.pop(small_parent)  # no longer a parent


def get_minimum_spanning_tree(graph):
    """ Given an undirected graph, finds a minimum spanning tree

    :param graph: UndirectedGraph object
    :return: tuple (cost, tree), where "cost" is the minimum cost of a tree, and "tree" is the tree itself
    (UndirectedGraph object)
    """
    no_vertices_in_graph = graph.get_number_vertices()

    all_edges = []
    for vertex_one in graph.parse_vertices():
        for vertex_two in graph.parse_edges(vertex_one):
            if vertex_one < vertex_two:  # don't take an edge twice
                all_edges.append((graph.get_edge_cost(vertex_one, vertex_two), vertex_one, vertex_two))
    random.shuffle(all_edges)
    all_edges.sort()  # we'll take the edges in order by their cost

    ancestor = dict()  # for each vertex, an ancestor (a vertex from the same tree which is closer to the root)
    tree_size = dict()  # the keys are vertices which are parents
    for vertex in graph.parse_vertices():  # in the beginning, each vertex is a tree
        ancestor[vertex] = vertex
        tree_size[vertex] = 1

    the_minimum_spanning_tree = UndirectedGraph(no_vertices_in_graph)  # the resulting tree itself
    total_cost = 0

    for (cost, vertex_one, vertex_two) in all_edges:
        parent_one = get_root(vertex_one, ancestor)
        parent_two = get_root(vertex_two, ancestor)
        if parent_one != parent_two:  # if different subtrees, unite them
            unite_trees(parent_one, parent_two, ancestor, tree_size)
            the_minimum_spanning_tree.add_edge(vertex_one, vertex_two, cost)
            total_cost += cost

    return total_cost, the_minimum_spanning_tree
