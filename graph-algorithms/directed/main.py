from directed_graph import load_graph_from_file, write_graph_to_file, count_paths_in_dag, \
    get_topological_order, count_lowest_cost_paths_in_dag
from tree_reconstruction import reconstruct_tree_in_pre, reconstruct_tree_in_post


def print_menu():
    print("[1] parse vertices")
    print("[2] parse inbound edges of a vertex")
    print("[3] parse outbound edges of a vertex")
    print("[4] get number of vertices")
    print("[5] get number of edges")
    print("[6] get edge cost")
    print("[7] set edge cost")
    print("[8] check edge's existence")
    print("[9] in degree of vertex")
    print("[10] out degree of vertex")
    print("[11] write the current graph to file 'output'")
    print("[12] topological sorting")
    print("[13] number of lowest cost paths between two vertices (needs DAG)")
    print("[14] number of paths between two vertices (needs DAG)")
    print("[15] reconstruct tree based on inorder and preorder lists")
    print("[16] reconstruct tree based on inorder and postorder lists")
    print("[123] exit")


if __name__ == '__main__':
    # graph = generate_random_graph(10, 25)
    # write_graph_to_file(graph, "random_graph3.txt")
    # exit(0)

    graph = load_graph_from_file("input")  # modify file "input" to change the graph that is loaded
    while True:
        print_menu()
        option = int(input(">"))

        if option == 1:
            print(graph.parse_vertices())
        elif option == 2:
            vertex = int(input("vertex="))
            print(graph.parse_inbound_edges(vertex))
        elif option == 3:
            vertex = int(input("vertex="))
            print(graph.parse_outbound_edges(vertex))
        elif option == 4:
            print(graph.get_number_vertices())
        elif option == 5:
            print(graph.get_number_edges())
        elif option == 6:
            a = int(input("a="))
            b = int(input("b="))
            print(graph.get_edge_cost(a, b))
        elif option == 7:
            a = int(input("a="))
            b = int(input("b="))
            cost = int(input("cost="))
            graph.set_edge_cost(a, b, cost)
        elif option == 8:
            a = int(input("a="))
            b = int(input("b="))
            print(graph.exists_edge(a, b))
        elif option == 9:
            vertex = int(input("vertex="))
            print(graph.get_in_degree(vertex))
        elif option == 10:
            vertex = int(input("vertex="))
            print(graph.get_out_degree(vertex))
        elif option == 11:
            write_graph_to_file(graph, "output")
        elif option == 12:
            vertices_sorted = get_topological_order(graph)
            if vertices_sorted == -1:
                print("Not a DAG")
            else:
                print(vertices_sorted)
        elif option == 13:
            a = int(input("a="))
            b = int(input("b="))
            number_of_walks = count_lowest_cost_paths_in_dag(graph, get_topological_order(graph), a, b)
            print(number_of_walks)
        elif option == 14:
            a = int(input("a="))
            b = int(input("b="))
            number_of_walks = count_paths_in_dag(graph, a, b)
            print(number_of_walks)
        elif option == 15:
            n = int(input("n="))
            inorder = []
            print("inorder:")
            for i in range(n):
                inorder.append(int(input()))
            preorder = []
            print("preorder:")
            for i in range(n):
                preorder.append(int(input()))
            parent = dict()
            reconstruct_tree_in_pre(inorder, preorder, parent)
            for vertex in range(1, n + 1):
                if vertex in parent:
                    print(f"The parent of {vertex} is {parent[vertex]}")
        elif option == 16:
            n = int(input("n="))
            inorder = []
            print("inorder:")
            for i in range(n):
                inorder.append(int(input()))
            postorder = []
            print("postorder:")
            for i in range(n):
                postorder.append(int(input()))
            parent = dict()
            reconstruct_tree_in_post(inorder, postorder, parent)
            for vertex in range(1, n + 1):
                if vertex in parent:
                    print(f"The parent of {vertex} is {parent[vertex]}")

        elif option == 123:
            break
