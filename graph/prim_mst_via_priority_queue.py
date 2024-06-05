# @file: prim_mst_via_priority_queue.py
# @brief: Prim's Minimum Spanning Tree Algorithm implementation in Python using a priority queue.
#         Since the graph uses a priority queue, the time complexity of the algorithm is O(E + VlogV) where V is the number of vertices in the graph
#         and E is the number of edges in the graph.

from typing import List, Tuple, Dict
import heapq

def prim_mst_via_priority_queue(graph_adjacency_list: Dict[str, List[Tuple[str, int]]]) -> Tuple[List[Tuple[str, str, int]], int]:

    # Select an arbitrary vertex as the starting vertex
    start_vertex: str = next(iter(graph_adjacency_list))

    # Initialize the priority queue with the starting vertex
    priority_queue: List[Tuple[int, str, str]] = []

    # Keep track of the vertices that are already visited
    visited_vertices: Dict[str, bool] = {vertex: False for vertex in graph_adjacency_list}

    # Keep track of the edges in the MST (The edges that connect the vertices in the MST)
    mst_edges: List[Tuple[str, str, int]] = []

    # Keep track of the total weight of the MST
    total_mst_weight: int = 0

    # Add the edges of the starting vertex to the priority queue
    # Note that heapq uses a min-heap and sort by the first element of the tuple
    visited_vertices[start_vertex] = True
    for neighbour_vertex, edge_weight in graph_adjacency_list[start_vertex]:
        heapq.heappush(priority_queue, (edge_weight, start_vertex, neighbour_vertex))

    # Iterate until the priority queue is empty
    while priority_queue:
        weight, source_vertex, destination_vertex = heapq.heappop(priority_queue)

        # If the destination vertex is already visited, skip the edge
        if visited_vertices[destination_vertex]:
            continue

        # Include the edge in the MST
        mst_edges.append((source_vertex, destination_vertex, weight))
        total_mst_weight += weight
        visited_vertices[destination_vertex] = True

        # Add the edges of the destination vertex to the priority queue
        for neighbour_vertex, edge_weight in graph_adjacency_list[destination_vertex]:
            if not visited_vertices[neighbour_vertex]:
                heapq.heappush(priority_queue, (edge_weight, destination_vertex, neighbour_vertex))

    return mst_edges, total_mst_weight

if __name__ == "__main__":
    # Graph is represented as an adjacency list
    # graph[node] = [(neighbour, weight), ...]   (A node has a list of neighbours with their corresponding edge weights)
    graph_adjacency_list: Dict[str, List[Tuple[str, int]]] = {
        'A': [('B', 2), ('D', 6)],
        'B': [('A', 2), ('C', 3), ('D', 8), ('E', 5)],
        'C': [('B', 3), ('E', 7)],
        'D': [('A', 6), ('B', 8), ('E', 9)],
        'E': [('B', 5), ('C', 7), ('D', 9)]
    }

    mst_edges, total_mst_weight = prim_mst_via_priority_queue(graph_adjacency_list)
    print("Minimum Spanning Tree Edges:")
    for edge in mst_edges:
        print(f"(Vertex {edge[0]} - Vertex {edge[1]}) with weight {edge[2]}")
    print(f"Total Weight of the MST: {total_mst_weight}")

# Minimum Spanning Tree Edges:
# (Vertex A - Vertex B) with weight 2
# (Vertex B - Vertex C) with weight 3
# (Vertex B - Vertex E) with weight 5
# (Vertex A - Vertex D) with weight 6
# Total Weight of the MST: 16
