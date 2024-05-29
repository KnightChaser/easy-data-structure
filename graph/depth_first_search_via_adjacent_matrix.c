/**
 * @file depth_first_search_via_adjacent_matrix.c
 * @brief A DFS(Depth First Search) demonstration implementation via to the graph structure
 *        which is implemented via adjacent matrix approach.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Graph structure (Represent a graph)
typedef struct graphViaAdjacentMatrix {
    unsigned int vertices;
    unsigned int edges;
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
    graph->vertices = vertices;
    graph->edges = 0;
    for (unsigned int row = 0; row < vertices; row++) {
        for (unsigned int column = 0; column < vertices; column++) {
            graph->adjacentMatrix[row][column] = false;
        }
    }
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph, Edge* edge) {
    if (edge->sourceEdge < graph->vertices && edge->destinationEdge < graph->vertices) {
        graph->adjacentMatrix[edge->sourceEdge][edge->destinationEdge] = true;
        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            graph->adjacentMatrix[edge->destinationEdge][edge->sourceEdge] = true;
        }
        graph->edges++;
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
    for (unsigned int column = 0; column < graph->vertices; column++) {
        printf("%02d  ", column);
    }
    printf("\n");
    for (unsigned int row = 0; row < graph->vertices; row++) {
        printf("%02d  ", row);
        for (unsigned int column = 0; column < graph->vertices; column++) {
            printf("%c   ", graph->adjacentMatrix[row][column] ? 'T' : 'F');
        }
        printf("\n");
    }
}

// Depth First Search (DFS) algorithm (recursive approach)
// 1. Start from the source vertex
// 2. Visit the source vertex
// 3. Recursively visit all the adjacent vertices of the source vertex
// (Note: the visited vertices are marked as visited to avoid infinite loop)
void depthFirstSearchViaAdjacentMatrixRecursive(GraphViaAdjacentMatrix* graph, unsigned int sourceVertex, bool visitedVertices[]) {
    visitedVertices[sourceVertex] = true;                                                       // Mark the source vertex as visited
    printf("VERTEX %u -> ", sourceVertex);                                              
    for (unsigned int vertex = 0; vertex < graph->vertices; vertex++) {
        // If the vertex is adjacent to the source vertex and not visited, recursively visit the vertex
        if (graph->adjacentMatrix[sourceVertex][vertex] && !visitedVertices[vertex]) {
            // Recursively visit the vertex only if the vertex is adjacent to the source vertex and not visited
            // Adjacency is checked via adjacent matrix. If 1, then the vertex is adjacent to the source vertex (connected by an edge)
            depthFirstSearchViaAdjacentMatrixRecursive(graph, vertex, visitedVertices);
        }
    }
}

// Depth First Search (DFS) algorithm (iterative approach)
// 1. Prepare the stacks for the vertices visited and the vertices to visit
// 2. Start from the source vertex
// 3. Visit the source vertex
// 4. Push the source vertex to the visited stack
// 5. Push the adjacent vertices of the source vertex to the vertices to visit stack
// 6. Pop the vertices to visit stack and visit the vertex
// 7. Repeat the steps 5-6 until the vertices to visit stack is empty
void depthFirstSearchViaAdjacentMatrixIterative(GraphViaAdjacentMatrix* graph, unsigned int sourceVertex) {
    bool visitedVertices[MAX_VERTICES] = {false};               // Initialize all the vertices as not visited
    unsigned int verticesStack[MAX_VERTICES];                   // Stack to store the vertices to visit
    unsigned int verticesStackTop = 0;                          // Stack top index
    verticesStack[verticesStackTop++] = sourceVertex;           // Push the source vertex to the stack

    while (verticesStackTop > 0) {
        // Pop the vertex from the stack and delete the vertex from the stack
        unsigned int currentVertex = verticesStack[--verticesStackTop];         
        if (!visitedVertices[currentVertex]) {
            visitedVertices[currentVertex] = true;                         // Mark the vertex as visited
            printf("VERTEX %u -> ", currentVertex);
        
        // Push the adjacent vertices of the current vertex to the stack (but only if the vertex is not visited yet)
        for (unsigned int vertex = 0; vertex < graph->vertices; vertex++) {
                if (graph->adjacentMatrix[currentVertex][vertex] && !visitedVertices[vertex]) {
                    verticesStack[verticesStackTop++] = vertex;
                }
            }
        }
    }
}

// Main function
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
    bool visitedVertices[5] = {false};      // Initialize all the vertices as not visited


    // Start from the vertex 0, and recursively visit all the vertices via DFS(recursive approach)
    printf("Depth First Search (DFS) via adjacent matrix(recursive): ");
    depthFirstSearchViaAdjacentMatrixRecursive(graph, 0, visitedVertices);
    printf("END\n");

    // Start from the vertex 0, and iteratively visit all the vertices via DFS(iterative approach)
    printf("Depth First Search (DFS) via adjacent matrix(iterative): ");
    depthFirstSearchViaAdjacentMatrixIterative(graph, 0);
    printf("END\n");

    return 0;
}

//     00  01  02  03  04  
// 00  F   T   T   F   F
// 01  T   F   T   F   F
// 02  T   T   F   T   F
// 03  F   F   T   F   T
// 04  F   F   F   T   F
// Depth First Search (DFS) via adjacent matrix(recursive): VERTEX 0 -> VERTEX 1 -> VERTEX 2 -> VERTEX 3 -> VERTEX 4 -> END