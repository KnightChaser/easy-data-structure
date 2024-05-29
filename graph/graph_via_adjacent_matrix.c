/**
 * @file graph_via_adjacent_matrix.c
 * @brief A graph structure implementation via adjacent matrix apporach.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct graphViaAdjacentMatrix {
    unsigned int numberOfVertices;      // The number of vertices in the graph
    unsigned int numberOfEdges;         // The number of edges in the graph
    bool adjacentMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphViaAdjacentMatrix;

// Edge structure (Represent a single edge in the graph)
typedef struct edge {
    unsigned int sourceEdge;
    unsigned int destinationEdge;
    bool isDirected;                    // Directed or undirected edge (If directed, source -> destination, otherwise source <-> destination)
} Edge;

// Create a graph via adjacent matrix
GraphViaAdjacentMatrix* createGraphViaAdjacentMatrix(unsigned int vertices) {
    GraphViaAdjacentMatrix* graph = (GraphViaAdjacentMatrix*) malloc(sizeof(GraphViaAdjacentMatrix));
    graph->numberOfVertices = vertices;
    graph->numberOfEdges = 0;
    for (unsigned int row = 0; row < vertices; row++) {
        for (unsigned int column = 0; column < vertices; column++) {
            graph->adjacentMatrix[row][column] = false;
        }
    }
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph, Edge* edge) {
    if (edge->sourceEdge < graph->numberOfVertices && edge->destinationEdge < graph->numberOfVertices) {
        graph->adjacentMatrix[edge->sourceEdge][edge->destinationEdge] = true;
        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            graph->adjacentMatrix[edge->destinationEdge][edge->sourceEdge] = true;
        }
        graph->numberOfEdges++;
    } else {
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Remove an edge from the graph
void removeEdgeFromGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph, Edge* edge) {
    if (edge->sourceEdge < graph->numberOfVertices && edge->destinationEdge < graph->numberOfVertices) {
        graph->adjacentMatrix[edge->sourceEdge][edge->destinationEdge] = false;
        if (!edge->isDirected) {
            // If the edge is undirected, remove the reverse edge
            graph->adjacentMatrix[edge->destinationEdge][edge->sourceEdge] = false;
        }
        graph->numberOfEdges--;
    } else {
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Print the graph via adjacent matrix
// Example output
//     00  01  02  03  04
// 00  T   T   F   F   F
// 01  T   T   T   F   F
// 02  F   T   T   T   F
// 03  F   F   T   T   T
// 04  F   F   F   T   T
void printGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph) {
    printf("    ");
    for (unsigned int column = 0; column < graph->numberOfVertices; column++) {
        printf("%02d  ", column);
    }
    printf("\n");
    for (unsigned int row = 0; row < graph->numberOfVertices; row++) {
        printf("%02d  ", row);
        for (unsigned int column = 0; column < graph->numberOfVertices; column++) {
            printf("%c   ", graph->adjacentMatrix[row][column] ? 'T' : 'F');
        }
        printf("\n");
    }
}

int main(void) {
    GraphViaAdjacentMatrix* graph = createGraphViaAdjacentMatrix(5);
    Edge edge1 = {0, 1, false};
    Edge edge2 = {0, 2, false};
    Edge edge3 = {1, 2, false};
    Edge edge4 = {2, 3, false};
    Edge edge5 = {3, 4, false};

    addEdgeToGraphViaAdjacentMatrix(graph, &edge1);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge2);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge3);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge4);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge5);

    printGraphViaAdjacentMatrix(graph);
    removeEdgeFromGraphViaAdjacentMatrix(graph, &edge3);
    printf("\n");
    printGraphViaAdjacentMatrix(graph);

    return 0;
}

//     00  01  02  03  04  
// 00  F   T   T   F   F
// 01  T   F   T   F   F
// 02  T   T   F   T   F
// 03  F   F   T   F   T
// 04  F   F   F   T   F
// 
//     00  01  02  03  04
// 00  F   T   T   F   F
// 01  T   F   F   F   F
// 02  T   F   F   T   F
// 03  F   F   T   F   T
// 04  F   F   F   T   F