# @file: grpah/kruskal_mst.py
# @brief: Kruskal's Minimum Spanning Tree Algorithm implementation in Python

from typing import List

# A structure to 51drepresent a weighted edge in graph
class Edge:
    def __init__(self, source: int, destination: int, weight: float) -> None:
        self.source: int        = source
        self.destination: int   = destination
        self.weight: float      = weight

# A structure to represent a connected, undirected and weighted graph with Kruskal's algorithm
class Graph:
    def __init__(self, number_of_vertices: int) -> None:
        self.number_of_vertices: int    = number_of_vertices
        self.edges: List[Edge]          = []                        # Managing edges in adjacency list format
        self.parent: List[int]          = list(range(number_of_vertices + 1))

    # Add an edge to the graph
    def add_edge(self, source: int, destination: int, weight: float) -> None:
        self.edges.append(Edge(source, destination, weight))

    # Find the parent of a vertex recursively
    def find(self, target: int) -> int:
        if self.parent[target] != target:
            self.parent[target] = self.find(self.parent[target])
        return self.parent[target]
    
    # Union of two subsets by rank
    def union(self, vertex1: int, vertex2: int) -> None:
        root1 = self.find(vertex1)
        root2 = self.find(vertex2)

        if root1 > root2:
            self.parent[root2] = root1
        else:
            self.parent[root1] = root2

    # Kruskal's Minimum Spanning Tree Algorithm
    def kruskal_mst(self) -> List[Edge]:
        mst: List[Edge] = []  # Resulting MST
        self.edges.sort(key=lambda edge: edge.weight)  

        for edge in self.edges:
            root1_parent: int = self.find(edge.source)
            root2_parent: int = self.find(edge.destination)

            # If the parents of two vertices are not same, then they do not form a cycle since they are not connected
            if root1_parent != root2_parent:
                mst.append(edge)                                # Add the edge to the MST
                self.union(edge.source, edge.destination)       # Union the two vertices

        return mst

# Example usage
if __name__ == "__main__":
    number_of_vertices = 4
    graph = Graph(number_of_vertices)
    graph.add_edge(source=1, destination=2, weight=2)
    graph.add_edge(source=1, destination=3, weight=4)
    graph.add_edge(source=2, destination=3, weight=5)
    graph.add_edge(source=2, destination=4, weight=7)
    graph.add_edge(source=3, destination=4, weight=10)

    mst = graph.kruskal_mst()
    print("Following are the edges in the constructed MST:")
    for edge in mst:
        print(f"Source: {edge.source}, Destination: {edge.destination}, Weight: {edge.weight}")

# Following are the edges in the constructed MST:
# Source: 1, Destination: 2, Weight: 2
# Source: 1, Destination: 3, Weight: 4
# Source: 2, Destination: 4, Weight: 7