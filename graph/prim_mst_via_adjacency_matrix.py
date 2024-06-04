# @file: prim_mst_via_adjacency_matrix.py
# @brief: Prim's Minimum Spanning Tree Algorithm implementation in Python using adjacency matrix to represent the graph
#         Since the grpah uses adjacency matrix, the time complexity of the algorithm is O(V^2) where V is the number of vertices in the graph
#         (Intuitively, there is a nested loop that iterate over all the vertices in the graph)

import numpy as np

def prim_mst_via_adjacency_list(graph_adjacency_list) -> tuple:
    number_of_vertices      = len(graph_adjacency_list)         # Number of vertices in the graph
    selected_vertices       = [False] * number_of_vertices      # Keep track of whether a vertex is selected or not in the MST
    minimum_edge_weights    = [np.inf] * number_of_vertices     # Keep track of the minimum edge weight of each vertex (initialize with infinity)
    parents_of_vertices     = [None] * number_of_vertices       # Stores the MST by recording the parent of each vertex in the MST

    # Start with the vertex 0
    minimum_edge_weights[0] = 0

    for _ in range(number_of_vertices):
        # Find the vertex with the minimum edge weight
        minimum_weight          = np.inf
        minimum_weight_vertex   = None

        for vertex in range(number_of_vertices):
            if not selected_vertices[vertex] and minimum_edge_weights[vertex] < minimum_weight:
                minimum_weight          = minimum_edge_weights[vertex]
                minimum_weight_vertex   = vertex

        # Include the chosen vertex in the MST. Now, it's visited and no longer a candidate for selection
        selected_vertices[minimum_weight_vertex] = True

        # Update the edge weights of the vertices adjacent to the chosen vertex
        for vertex in range(number_of_vertices):
            if graph_adjacency_list[minimum_weight_vertex][vertex] != 0 and                             \
                not selected_vertices[vertex] and                                                       \
                graph_adjacency_list[minimum_weight_vertex][vertex] < minimum_edge_weights[vertex]:
                # Update the minimum edge weight of the vertex only if
                # 1. The edge between the chosen vertex and the vertex is not zero(edge between the vertex and itself exists)
                # 2. The vertex is not already selected in the MST
                # 3. The edge weight between the chosen vertex and the vertex is less than the current minimum edge weight of the vertex
                minimum_edge_weights[vertex] = graph_adjacency_list[minimum_weight_vertex][vertex]
                parents_of_vertices[vertex]  = minimum_weight_vertex

    return parents_of_vertices, minimum_edge_weights

if __name__ == "__main__":
    graph_adjacency_matrix = np.array([
        [0, 2, 0, 6, 0],
        [2, 0, 3, 8, 5],
        [0, 3, 0, 0, 7],
        [6, 8, 0, 0, 9],
        [0, 5, 7, 9, 0]
    ])

    parents_of_vertices, minimum_edge_weights = prim_mst_via_adjacency_list(graph_adjacency_matrix)

    print(f"Edge \t\t Weight")
    for vertex in range(1, len(parents_of_vertices)):
        print(f"{parents_of_vertices[vertex]} - {vertex} \t\t {minimum_edge_weights[vertex]}")

    print(f"The minimum spanning tree has a total weight of {sum(minimum_edge_weights)}")

# Edge             Weight
# 0 - 1            2
# 1 - 2            3
# 0 - 3            6
# 1 - 4            5
# The minimum spanning tree has a total weight of 16