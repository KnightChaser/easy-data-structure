# file: graph_via_adjacent_list.py
# brief: A general implementation of a graph(data structure) in Python with class
#        Basically, this is implemented using an adjacency list.

from typing import Dict, List, Tuple

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
    # We have an edge from source_vertex to destination_vertex (directed graph)
    def add_edge(self, source_vertex: str, destination_vertex: str, directed: bool) -> None:
        if not source_vertex or not destination_vertex:
            raise ValueError("Source and destination vertices cannot be empty")
        self.graph[source_vertex].append(destination_vertex)
        if not directed:
            # If the graph is undirected, add an edge from destination_vertex to source_vertex
            self.graph[destination_vertex].append(source_vertex)

    # Remove a vertex from the graph
    def remove_vertex(self, vertex: str) -> None:
        if not vertex:
            raise ValueError("Vertex cannot be empty")
        if vertex in self.graph:
            del self.graph[vertex]

            # Remove the target vertex from all other vertices' adjacency lists
            for vertices in self.graph:
                if vertex in self.graph[vertices]:
                    self.graph[vertices].remove(vertex)
        else:
            raise ValueError("Vertex does not exist")
        
    # Remove an edge from the graph
    def remove_edge(self, source_vertex: str, destination_vertex: str) -> None:
        if not source_vertex or not destination_vertex:
            raise ValueError("Source and destination vertices cannot be empty")
        if source_vertex in self.graph:

            # Remove the edge from source_vertex to destination_vertex
            if destination_vertex in self.graph[source_vertex]:
                self.graph[source_vertex].remove(destination_vertex)
            else:
                raise ValueError("Edge does not exist")

    # Print the graph
    def print_graph(self) -> None:
        for vertex in self.graph:
            print(f"{vertex} -> {self.graph[vertex]}")

    # Get the number of vertices in the graph
    def get_num_vertices(self) -> int:
        return len(self.graph)
    
    # Get the number of edges in the graph
    def get_num_edges(self) -> int:
        num_edges = 0
        for vertex in self.graph:
            num_edges += len(self.graph[vertex])
        return num_edges
    
# Now, let's use the graph.
graph = Graph()

graph.add_vertex("A")
graph.add_vertex("B")
graph.add_vertex("C")
graph.add_vertex("D")
graph.add_vertex("E")
graph.add_vertex("F")

graph.add_edge(source_vertex="A", destination_vertex="B", directed=True)
graph.add_edge(source_vertex="A", destination_vertex="C", directed=True)
graph.add_edge(source_vertex="B", destination_vertex="D", directed=False)
graph.add_edge(source_vertex="C", destination_vertex="E", directed=True)
graph.add_edge(source_vertex="D", destination_vertex="E", directed=True)
graph.add_edge(source_vertex="E", destination_vertex="F", directed=False)
graph.add_edge(source_vertex="F", destination_vertex="A", directed=True)

graph.print_graph()

print(f"Number of vertices: {graph.get_num_vertices()}")
print(f"Number of edges: {graph.get_num_edges()}")
print("\n")

graph.remove_vertex("A")
graph.remove_edge(source_vertex="B", destination_vertex="D")
graph.print_graph()

print(f"Number of vertices: {graph.get_num_vertices()}")
print(f"Number of edges: {graph.get_num_edges()}")

# A -> ['B', 'C']
# B -> ['D']
# C -> ['E']
# D -> ['B', 'E']
# E -> ['F']
# F -> ['E', 'A']
# Number of vertices: 6
# Number of edges: 9
# 
# 
# B -> []
# C -> ['E']
# D -> ['B', 'E']
# E -> ['F']
# F -> ['E']
# Number of vertices: 5
# Number of edges: 5