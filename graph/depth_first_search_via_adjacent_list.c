/**
 * @file depth_first_search_via_adjacent_list.c
 * @brief A DFS(Depth First Search) demonstration implementation via to the graph structure
 *        which is implemented via adjacent list approach.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Edge structure (Represent a single edge in the graph)
typedef struct edge {
    unsigned int sourceEdge;                    // The source vertex of the edge
    unsigned int destinationEdge;               // The destination vertex of the edge
    bool isDirected;                            // Directed or undirected edge (If directed, source -> destination, otherwise source <-> destination)
} Edge;

// A single node in the graph (Represent a single vertex in the graph)
typedef struct graphNode {
    unsigned int vertex;                        // The number of the vertex
    struct graphNode* next;                     // The next node in the linked list
} GraphNode;

// Graph structure
typedef struct graphViaAdjacentList {
    unsigned int numberOfVertices;              // The number of vertices in the graph
    unsigned int numberOfEdges;                 // The number of edges in the graph
    GraphNode *adjacentList[MAX_VERTICES];      // The adjacent list of the graph (Each vertex has a linked list of the connected vertices)
} GraphViaAdjacentList;

// Create a graph via adjacent list
GraphViaAdjacentList* createGraphViaAdjacentList(unsigned int numberOfVertices) {
    GraphViaAdjacentList* graph = (GraphViaAdjacentList*) malloc(sizeof(GraphViaAdjacentList));
    graph->numberOfVertices = numberOfVertices;
    graph->numberOfEdges = 0;
    memset(graph->adjacentList, 0, sizeof(graph->adjacentList));
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceEdge < MAX_VERTICES && edge->destinationEdge < MAX_VERTICES) {
        // Add the edge to the source vertex's linked list
        GraphNode* node = (GraphNode*) malloc(sizeof(GraphNode));
        node->vertex = edge->destinationEdge;
        node->next = graph->adjacentList[edge->sourceEdge];
        graph->adjacentList[edge->sourceEdge] = node;
        graph->numberOfEdges++;

        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            GraphNode* reverseNode = (GraphNode*) malloc(sizeof(GraphNode));
            reverseNode->vertex = edge->sourceEdge;
            reverseNode->next = graph->adjacentList[edge->destinationEdge];
            graph->adjacentList[edge->destinationEdge] = reverseNode;
            graph->numberOfEdges++;  // Consider the reverse edge as well
        }
    } else {
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Print the graph via adjacent list
void printGraphViaAdjacentList(GraphViaAdjacentList* graph) {
    for (unsigned int vertex = 0; vertex < graph->numberOfVertices; vertex++) {
        GraphNode* node = graph->adjacentList[vertex];
        printf("VERTEX %u ->", vertex);
        while (node != NULL) {
            printf(" %u", node->vertex);
            node = node->next;
        }
        printf("\n");
    }
}

// Depth First Search (DFS) algorithm in recursive approach
void depthFirstSearchViaAdjacentListRecursive(GraphViaAdjacentList* graph, unsigned int sourceVertex, bool visitedVertices[]) {
    visitedVertices[sourceVertex] = true;
    printf("VERTEX %u ->", sourceVertex);

    // Get the source vertex's linked list
    GraphNode* node = graph->adjacentList[sourceVertex];

    while (node != NULL) {
        // For each adjacent vertex, if it is not visited, recursively call the DFS function
        if (!visitedVertices[node->vertex])
            depthFirstSearchViaAdjacentListRecursive(graph, node->vertex, visitedVertices);
        node = node->next;
    }
}

// Depth First Search (DFS) algorithm in iterative approach (via stack)
void depthFirstSearchViaAdjacentListIterative(GraphViaAdjacentList* graph, unsigned int sourceVertex) {
    bool visitedVertices[MAX_VERTICES];
    memset(visitedVertices, 0, sizeof(visitedVertices));

    // Create a stack to keep track of the vertices. Initially, the stack is empty
    unsigned int verticesStack[MAX_VERTICES];
    unsigned int verticesStackTopIndex = 0;

    // Push the source vertex to the stack
    verticesStack[verticesStackTopIndex++] = sourceVertex;

    while (verticesStackTopIndex > 0) {
        // Pop a vertex from the stack
        unsigned int currentVertex = verticesStack[--verticesStackTopIndex];

        if (!visitedVertices[currentVertex]) {
            visitedVertices[currentVertex] = true;
            printf("VERTEX %u ->", currentVertex);

            // Get the current vertex's linked list
            GraphNode* node = graph->adjacentList[currentVertex];
            while (node != NULL) {
                if (!visitedVertices[node->vertex]) {
                    // For each unvisited adjacent vertex of the current vertex, push it to the stack and visit it
                    verticesStack[verticesStackTopIndex++] = node->vertex;
                }
                node = node->next;
            }
        }
    }
}

// Main function to test the graph and DFS implementation
int main() {
    unsigned int numberOfVertices = 5;
    GraphViaAdjacentList* graph = createGraphViaAdjacentList(numberOfVertices);

    Edge edges[] = {
        {0, 1, false},
        {0, 4, false},
        {1, 2, false},
        {1, 3, false},
        {1, 4, false},
        {2, 3, false},
        {3, 4, false}
    };

    for (unsigned int index = 0; index < (unsigned int)sizeof(edges) / sizeof(edges[0]); index++)
        addEdgeToGraphViaAdjacentList(graph, &edges[index]);

    printGraphViaAdjacentList(graph);

    // Perform the DFS algorithm
    printf("DFS Recursive:");
    bool visitedVertices[MAX_VERTICES] = {0};
    depthFirstSearchViaAdjacentListRecursive(graph, 0, visitedVertices);
    printf("END\n");

    // Perform the DFS algorithm iteratively
    printf("DFS Iterative:");
    depthFirstSearchViaAdjacentListIterative(graph, 0);
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
// Depth First Search (DFS) via adjacent matrix(iterative): VERTEX 0 -> VERTEX 2 -> VERTEX 3 -> VERTEX 4 -> VERTEX 1 -> END