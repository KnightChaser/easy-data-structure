/**
 * @file kruskal_mst.cpp
 * @brief Kruskal's Minimum Spanning Tree Algorithm implementation in C++ language
 */
//

#include <iostream>
#include <vector>
#include <algorithm>

// Define the structure for edges
class Edge {
public:
    int source;
    int destination;
    double weight;

    Edge(int source, int destination, double weight) {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
};

// Define the structure for disjoint set
// Disjoint set is a data structure that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
class DisjointSet {
private:
    std::vector<int> parent;    // Array to store the parent of vertices
    std::vector<int> rank;      // Array to store the rank of vertices (height of the tree)
public:
    // constructor
    DisjointSet(unsigned int numberOfVertices) {
        this->parent.resize(numberOfVertices);
        this->rank.resize(numberOfVertices);
        for (unsigned int index = 0; index < numberOfVertices; index++) {
            this->parent[index] = index;
            this->rank[index] = 0;
        }
    }

    int findParentVertex(int targetVertex);
    void unite(int vertex1, int vertex2);
};

// Function to find the parent of a vertex
int DisjointSet::findParentVertex(int targetVertex) {
    if (this->parent[targetVertex] != targetVertex)
        this->parent[targetVertex] = findParentVertex(this->parent[targetVertex]);
    return this->parent[targetVertex];
}

// Function to unite (union) two sets
void DisjointSet::unite(int vertex1, int vertex2) {
    int parentOfVertex1 = findParentVertex(vertex1);
    int parentOfVertex2 = findParentVertex(vertex2);

    // Union by rank
    // If the rank of the parent of vertex1 is less than the rank of the parent of vertex2, 
    // then make the parent of vertex1 as the parent of vertex2
    if (this->rank[parentOfVertex1] < this->rank[parentOfVertex2]) {
        this->parent[parentOfVertex1] = parentOfVertex2;
    } else if (this->rank[parentOfVertex1] > this->rank[parentOfVertex2]) {
        this->parent[parentOfVertex2] = parentOfVertex1;
    } else {
        this->parent[parentOfVertex2] = parentOfVertex1;
        this->rank[parentOfVertex1]++;
    }
}

// A graph class with Kruskal's MST algorithm
class KruskalMSTGraph {
private:
    std::vector<Edge> edges;
    unsigned int numberOfVertices;
public:
    KruskalMSTGraph(unsigned int numberOfVertices) {
        this->numberOfVertices = numberOfVertices;
    }

    void addEdge(int source, int destination, double weight);
    void findMST();
};    

// Function to add an edge to the graph
void KruskalMSTGraph::addEdge(int source, int destination, double weight) {
    // Note that the vertices array is 0-based
    this->edges.push_back(Edge(source - 1, destination - 1, weight)); 
}

// Kruskal's Algorithm to find the Minimum Spanning Tree
void KruskalMSTGraph::findMST() {
    // Sort the edges based on their weights in non-decreasing order
    std::sort(this->edges.begin(), this->edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Create a disjoint set
    DisjointSet disjointSet(this->numberOfVertices);

    double minimumSpanningTreeWeight = 0;
    std::cout << "Following are the edges in the constructed MST" << std::endl;
    for (Edge& edge : edges) {
        int parentOfSourceVertex = disjointSet.findParentVertex(edge.source);
        int parentOfDestinationVertex = disjointSet.findParentVertex(edge.destination);

        if (parentOfSourceVertex != parentOfDestinationVertex) {
            // If the parent of source vertex is not equal to the parent of destination vertex,
            // then unite (union) the two sets and add the edge to the minimum spanning tree
            disjointSet.unite(parentOfSourceVertex, parentOfDestinationVertex);
            minimumSpanningTreeWeight += edge.weight;
            std::cout << "(" << edge.source + 1 << ", " << edge.destination + 1 << ") => Cost: " << edge.weight << std::endl;
        }
    }

    std::cout << "Minimum Spanning Tree Weight: " << minimumSpanningTreeWeight << std::endl;
}

int main(void) {
    KruskalMSTGraph graph(4);    // A graph with 4 vertices
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 10);

    graph.findMST();

    return 0;
}

// (1, 2) => Cost: 2
// (1, 3) => Cost: 4
// (2, 4) => Cost: 7
// Minimum Spanning Tree Weight: 13