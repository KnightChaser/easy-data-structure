/**
 * @file kruskal_mst.c
 * @brief Kruskal's Minimum Spanning Tree Algorithm implementation in C language
 */
//

#include <stdio.h>
#include <stdlib.h>

// Define the structure for edges
typedef struct Edge {
    int source;
    int destination;
    int weight;
}Edge;

// Comparing function to use in sorting
int comparator(const void* edge1, const void* edge2) {
    struct Edge* e1 = (struct Edge*)edge1;
    struct Edge* e2 = (struct Edge*)edge2;
    return e1->weight - e2->weight;
}

// Initializing of parent[] and rank[] arrays
void makeSet(int* parent, int* rank, int numberOfVertices) {
    for (int index = 0; index < numberOfVertices; index++) {
        parent[index] = index;
        rank[index] = 0;
    }
}

// Function to find the parent of a vertex
int findParentVertex(int* parent, int targetVertex) {
    if (parent[targetVertex] == targetVertex)
        return targetVertex;
    return parent[targetVertex] = findParentVertex(parent, parent[targetVertex]);
}

// Function to unite (union) two sets
void unionSet(int vertex1, int vertex2, int* parent, int* rank) {
    int parentOfVertex1 = findParentVertex(parent, vertex1);
    int parentOfVertex2 = findParentVertex(parent, vertex2);

    if (rank[parentOfVertex1] < rank[parentOfVertex2]) {
        parent[parentOfVertex1] = parentOfVertex2;
    } else if (rank[parentOfVertex1] > rank[parentOfVertex2]) {
        parent[parentOfVertex2] = parentOfVertex1;
    } else {
        parent[parentOfVertex2] = parentOfVertex1;
        rank[parentOfVertex1]++;
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void kruskalAlgorithm(int numberOfEdges, struct Edge edges[]) {
    // Sort the edges based on their weights
    qsort(edges, numberOfEdges, sizeof(struct Edge), comparator);

    int parentOfVertices[numberOfEdges];        // Array to store the parent of vertices
    int rankOfVertices[numberOfEdges];          // Array to store the rank of vertices (height of the tree)

    // Initialize the parent[] and rank[] arrays
    makeSet(parentOfVertices, rankOfVertices, numberOfEdges);

    int minimumSpanningTreeWeight = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int index = 0; index < numberOfEdges; index++) {
        int parentOfVertex1 = findParentVertex(parentOfVertices, edges[index].source);          // Find the parent of source vertex
        int parentOfVertex2 = findParentVertex(parentOfVertices, edges[index].destination);     // Find the parent of destination vertex

        if (parentOfVertex1 != parentOfVertex2) {
            // If the parent of source vertex is not equal to the parent of destination vertex,
            // then unite (union) the two sets and add the edge to the minimum spanning tree
            unionSet(parentOfVertex1, parentOfVertex2, parentOfVertices, rankOfVertices);
            minimumSpanningTreeWeight += edges[index].weight;
            printf("(%d, %d) => Cost: %d\n", edges[index].source, edges[index].destination, edges[index].weight);
        }
    }

    printf("Minimum Spanning Tree Weight: %d\n", minimumSpanningTreeWeight);
}

int main(void) {
    // A graph with 4 vertices and 5 edges
    Edge edges[] = {
        {1, 2, 2},
        {1, 3, 4},
        {2, 3, 5},
        {2, 4, 7},
        {3, 4, 10}
    };

    int numberOfEdges = sizeof(edges) / sizeof(edges[0]);
    kruskalAlgorithm(numberOfEdges, edges);

    return 0;
}


// Following are the edges in the constructed MST
// (1, 2) => Cost: 2
// (1, 3) => Cost: 4
// (2, 4) => Cost: 7
// Minimum Spanning Tree Weight: 13