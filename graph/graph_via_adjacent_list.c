/**
 * @file graph_via_adjacent_list.c
 * @brief A graph structure implementation via adjacent list apporach instead of adjacent matrix.
 */
//

#include <complex.h>
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
    unsigned int vertices;                      // The number of vertices in the graph
    unsigned int edges;                         // The number of edges in the graph
    GraphNode *adjacentList[MAX_VERTICES];      // The adjacent list of the graph (Each vertex has a linked list of the connected vertices)
} GraphViaAdjacentList;

// Create a graph via adjacent list
GraphViaAdjacentList* createGraphViaAdjacentList() {
    GraphViaAdjacentList* graph = (GraphViaAdjacentList*) malloc(sizeof(GraphViaAdjacentList));
    graph->vertices = 0;
    graph->edges = 0;
    memset(graph->adjacentList, 0, sizeof(graph->adjacentList));
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceEdge < MAX_VERTICES && edge->destinationEdge < MAX_VERTICES) {
        GraphNode* node = (GraphNode*) malloc(sizeof(GraphNode));
        node->vertex = edge->destinationEdge;
        node->next = graph->adjacentList[edge->sourceEdge];
        graph->adjacentList[edge->sourceEdge] = node;
        graph->edges++;

        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            GraphNode* reverseNode = (GraphNode*) malloc(sizeof(GraphNode));
            reverseNode->vertex = edge->sourceEdge;
            reverseNode->next = graph->adjacentList[edge->destinationEdge];
            graph->adjacentList[edge->destinationEdge] = reverseNode;
            graph->edges++;                     // Consider the reverse edge as well
        }
    } else {
        // Invalid edge source or destination
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Remove an edge from the graph
// Find the edge in the source vertex and remove it
// Removing procedure is almost similar to handle the removing elements in the linked list
void removeEdgeFromGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceEdge < MAX_VERTICES && edge->destinationEdge < MAX_VERTICES) {
        GraphNode* node = graph->adjacentList[edge->sourceEdge];                // Find the edge in the source vertex (This is the linked list of the edge)
        GraphNode* previousNode = NULL;                                         // Keep track of the previous node
        while (node != NULL) {
            // Find the edge in the source vertex
            if (node->vertex == edge->destinationEdge) {
                // Remove the edge (we found the edge in the source vertex)
                if (previousNode == NULL) {
                    // The edge is the first edge in the list
                    graph->adjacentList[edge->sourceEdge] = node->next;
                } else {
                    // The edge is not the first edge in the list
                    previousNode->next = node->next;
                }
                free(node);
                graph->edges--;
                break;
            }
            // We didn't find the edge yet, continue to the next node
            previousNode = node;
            node = node->next;
        }

        // If the edge is undirected, remove the reverse edge as well
        if (!edge->isDirected) {
            // If the edge is undirected, remove the reverse edge
            node = graph->adjacentList[edge->destinationEdge];
            previousNode = NULL;
            while (node != NULL) {
                if (node->vertex == edge->sourceEdge) {
                    // Remove the edge (we found the edge in the destination vertex)
                    if (previousNode == NULL) {
                        graph->adjacentList[edge->destinationEdge] = node->next;
                    } else {
                        previousNode->next = node->next;
                    }
                    free(node);
                    graph->edges--;
                    break;
                }
                previousNode = node;
                node = node->next;
            }
        }
    } else {
        // Invalid edge source or destination
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Print the graph
void printGraphViaAdjacentList(GraphViaAdjacentList* graph) {
    for (unsigned int vertex = 0; vertex < MAX_VERTICES; vertex++) {
        GraphNode* node = graph->adjacentList[vertex];
        if (node != NULL) {
            printf("Vertex %d is connected to: ", vertex);
            while (node != NULL) {
                printf("%d ", node->vertex);
                node = node->next;
            }
            printf("\n");
        }
    }
}

// Free the graph memory (Free the graph and all the nodes in the graph)
void freeGraphViaAdjacentList(GraphViaAdjacentList *graph) {
    for (unsigned int vertex = 0; vertex < MAX_VERTICES; vertex++) {
        GraphNode* node = graph->adjacentList[vertex];
        while (node != NULL) {
            // Traverse the linked list and free the memory
            GraphNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    printf("Freed the graph memory\n");
}

// Main function
int main(void) {
    GraphViaAdjacentList* graph = createGraphViaAdjacentList();

    addEdgeToGraphViaAdjacentList(graph, &(Edge){0, 1, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){0, 2, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){1, 2, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){2, 3, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){3, 4, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){4, 0, false});
    
    printGraphViaAdjacentList(graph);
    printf("\n");

    removeEdgeFromGraphViaAdjacentList(graph, &(Edge){1, 2, false});
    printGraphViaAdjacentList(graph);

    return 0;
}

// Vertex 0 is connected to: 4 2 1 
// Vertex 1 is connected to: 2 0
// Vertex 2 is connected to: 3 1 0
// Vertex 3 is connected to: 4 2
// Vertex 4 is connected to: 0 3
// 
// Vertex 0 is connected to: 4 2 1
// Vertex 1 is connected to: 0
// Vertex 2 is connected to: 3 0
// Vertex 3 is connected to: 4 2
// Vertex 4 is connected to: 0 3