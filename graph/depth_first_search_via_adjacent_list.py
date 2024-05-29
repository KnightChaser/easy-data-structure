# file: depth_first_search_via_adjacent_list.py
# brief: DFS(Depth First Search) implementation of graph which is represented by adjacent list.

from typing import List, Dict

class Graph:
    def __init__(self) -> None:
        self.graph: Dict[str, List[str]] = {}

    # Add a new vertex to the graph
    def add_vertex(self, vertex: str) -> None:
        if not vertex:
            raise ValueError("Vertex cannot be empty")
        if vertex not in self.graph:
            self.graph[vertex] = []
        else:
            raise ValueError("Vertex already exists")
        
    # Add a new edge to the graph
    def add_edge(self, source_vertex: str, destination_vertex: str, directed: bool) -> None:
        if not source_vertex or not destination_vertex:
            raise ValueError("Source and destination vertices cannot be empty")
        self.graph[source_vertex].append(destination_vertex)
        if not directed:
            # If the graph is undirected, add an edge from destination_vertex to source_vertex
            self.graph[destination_vertex].append(source_vertex)

    # Removal parts are not implemented for brevity.

    # Depth First Search
    def dfs(self, vertex: str) -> None:
        visited = set()
        self._dfs(vertex, visited)

    # Helper function for DFS
    def _dfs(self, vertex: str, visited: set) -> None:
        visited.add(vertex)
        print(vertex, end=" ")

        # Recur for all the vertices adjacent to this vertex if they are not visited
        for neighbour in self.graph[vertex]:
            if neighbour not in visited:
                self._dfs(neighbour, visited)

# Usage
if __name__ == "__main__":
    graph = Graph()
    graph.add_vertex("A")
    graph.add_vertex("B")
    graph.add_vertex("C")
    graph.add_vertex("D")
    graph.add_vertex("E")
    graph.add_vertex("F")
    graph.add_vertex("G")

    graph.add_edge("A", "B", directed=True)
    graph.add_edge("A", "C", directed=True)
    graph.add_edge("B", "D", directed=True)
    graph.add_edge("B", "E", directed=True)
    graph.add_edge("C", "F", directed=True)
    graph.add_edge("C", "G", directed=True)

    graph.dfs("A")

# A B D E C F G 