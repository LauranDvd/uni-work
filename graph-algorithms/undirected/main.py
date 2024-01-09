from undirected_graph import write_graph_to_file, UndirectedGraph, load_graph_from_file, \
    get_connected_components, get_minimum_spanning_tree


def print_menu():
    print("[1] parse vertices")
    print("[2] parse edges of a vertex")
    print("[3] get number of vertices")
    print("[4] get number of edges")
    print("[5] get edge cost")
    print("[6] set edge cost")
    print("[7] check edge's existence")
    print("[8] degree of vertex")
    print("[9] write the current graph to file 'output'")
    print("[10] compute the connected components")
    print("[11] find a minimum spanning tree")


if __name__ == '__main__':
    # note: read from file "input", write to file "output"
    graph = UndirectedGraph()
    load_graph_from_file(graph, "input")  # modify file "input" to change the graph that is loaded

    while True:
        print_menu()
        option = int(input(">"))

        if option == 1:
            print(graph.parse_vertices())
        elif option == 2:
            vertex = int(input("vertex="))
            print(graph.parse_edges(vertex))
        elif option == 3:
            print(graph.get_number_vertices())
        elif option == 4:
            print(graph.get_number_edges())
        elif option == 5:
            a = int(input("a="))
            b = int(input("b="))
            print(graph.get_edge_cost(a, b))
        elif option == 6:
            a = int(input("a="))
            b = int(input("b="))
            cost = int(input("cost="))
            graph.set_edge_cost(a, b, cost)
        elif option == 7:
            a = int(input("a="))
            b = int(input("b="))
            print(graph.exists_edge(a, b))
        elif option == 8:
            vertex = int(input("vertex="))
            print(graph.get_degree(vertex))
        elif option == 9:
            write_graph_to_file(graph, "output")
        elif option == 10:
            components = get_connected_components(graph)
            print("The connected components are the following subgraphs:")
            for component in components:  # "component" is of class UndirectedGraph
                print("The vertices of a component: ", component.parse_vertices())
        elif option == 11:
            cost, mst = get_minimum_spanning_tree(graph)
            print("The cost is", cost)
            print("The edges that are kept are:")
            for vertex_one in mst.parse_vertices():
                for vertex_two in mst.parse_edges(vertex_one):
                    if vertex_one < vertex_two:
                        edge_cost = mst.get_edge_cost(vertex_one, vertex_two)
                        print("From", vertex_one, "to", vertex_two, "with cost", edge_cost)
