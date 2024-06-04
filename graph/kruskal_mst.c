/**
 * @file kruskal_mst.c
 * @brief Kruskal's Minimum Spanning Tree Algorithm implementation in C language
 */
//

#include <stdio.h>
#include <stdlib.h>

// Comparing function to use in sorting
int comparator(const void * vertex1, const void* vertex2) {
    const int(*x)[3] = vertex1;
    const int(*y)[3] = vertex2;

    return (*x)[2] - (*y)[2];
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

// Function to unite(unioning) two sets
void unionSet(int vertex1, int vertex2, int* parent, int* rank) {
    // Find the parents of the given vertices
    int parentOfVertex1 = findParentVertex(parent, vertex1);
    int parentOfVertex2 = findParentVertex(parent, vertex2);

    if (rank[parentOfVertex1] < rank[parentOfVertex2]) {
        parent[parentOfVertex1] = parentOfVertex2;
    } else if (rank[parentOfVertex1] > rank[parentOfVertex2]) {
        parent[parentOfVertex2] = parentOfVertex1;
    } else {
        // If the ranks are equal, then make one as parent and increment its rank
        parent[parentOfVertex2] = parentOfVertex1;
        rank[parentOfVertex2]++;
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void kruskalAlgorithm(int numberOfEdges, int edges[numberOfEdges][3]) {
    // Sort the edges based on their weights
    qsort(edges, numberOfEdges, sizeof(edges[0]), comparator);

    int parentOfVertices[numberOfEdges];
    int rankOfVertices[numberOfEdges];

    // Initialize the parent[] and rank[] arrays
    makeSet(parentOfVertices, rankOfVertices, numberOfEdges);

    // Initialize the minimum spanning tree weight
    int minimumSpanningTreeWeight = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int index = 0; index < numberOfEdges; index++) {
        int parentOfVertex1 = findParentVertex(parentOfVertices, edges[index][0]);
        int parentOfVertex2 = findParentVertex(parentOfVertices, edges[index][1]);
        int weight = edges[index][2]; // We consider undirected graph

        // If the parents are different then the edge is not forming a cycle
        // Because the edge is connecting two different sets
        if (parentOfVertex1 != parentOfVertex2) {
            unionSet(parentOfVertex1, parentOfVertex2, parentOfVertices, rankOfVertices);
            minimumSpanningTreeWeight += weight;
            printf("(%d, %d) => Cost: %d\n", edges[index][0], edges[index][1], weight);
        }
    }

    printf("Minimum Spanning Tree Weight: %d\n", minimumSpanningTreeWeight);
}

int main(void) {
    int edges[5][3] = {
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