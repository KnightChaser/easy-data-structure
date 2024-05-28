/**
 * @file graph_via_adjacent_list_dynamic.c
 * @brief A graph structure implementation via adjacent list apporach instead of adjacent matrix.
 *        Instead of using a fixed size array, this implementation uses dynamic memory allocation.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

// Edge structure (Represent a single edge in the graph)
typedef struct edge {
    unsigned int sourceEdge;                    // The source vertex of the edge
    unsigned int destinationEdge;               // The destination vertex of the edge
    bool isDirected;                            // Directed or undirected edge (If directed, source -> destination, otherwise source <-> destination)
} Edge;

// A single node in the graph (Represent a single vertex in the graph)
typedef struct graphNode {
    unsigned int vertex;                        // The identifying number of the vertex
    struct graphNode* next;                     // The next node in the linked list
} GraphNode;

// Graph structure
typedef struct graphViaAdjacentList {
    unsigned int numberOfVertices;              // The number of vertices in the graph
    unsigned int numberOfEdges;                 // The number of edges in the graph
    GraphNode **adjacentList;                   // The adjacent list of the graph (Each vertex has a linked list of the connected vertices)
} GraphViaAdjacentList;

// Create a graph via adjacent list
GraphViaAdjacentList* createGraphViaAdjacentList(unsigned int numberOfVertices) {
    GraphViaAdjacentList* graph = (GraphViaAdjacentList*) malloc(sizeof(GraphViaAdjacentList));
    graph->numberOfVertices = numberOfVertices;
    graph->numberOfEdges = 0;

    // Allocate memory for the adjacent list array and initialize it
    graph->adjacentList = (GraphNode**) malloc(numberOfVertices * sizeof(GraphNode*));
    memset(graph->adjacentList, 0, numberOfVertices * sizeof(GraphNode*));
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceEdge < graph->numberOfVertices && edge->destinationEdge < graph->numberOfVertices) {
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
            graph->numberOfEdges++;                     // Consider the reverse edge as well
        }
    } else {
        // Expand the graph if the edge source or destination is out of bounds (realloc)
        unsigned int newNumberOfVertices = edge->sourceEdge > edge->destinationEdge ? edge->sourceEdge + 1 : edge->destinationEdge + 1;
        GraphNode** newAdjacentList = (GraphNode**) malloc(newNumberOfVertices * sizeof(GraphNode*));
        memset(newAdjacentList, 0, newNumberOfVertices * sizeof(GraphNode*));
        memcpy(newAdjacentList, graph->adjacentList, graph->numberOfVertices * sizeof(GraphNode*));
        free(graph->adjacentList);
        printf("Expanded the graph from %d to %d vertices\n", graph->numberOfVertices, newNumberOfVertices);
        graph->adjacentList = newAdjacentList;
        graph->numberOfVertices = newNumberOfVertices;

        // Add the edge again
        addEdgeToGraphViaAdjacentList(graph, edge);
    }
}

// Remove an edge from the graph
void removeEdgeFromGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceEdge < graph->numberOfVertices && edge->destinationEdge < graph->numberOfVertices) {
        // Remove the edge from the source vertex
        GraphNode* currentNode = graph->adjacentList[edge->sourceEdge];
        GraphNode* previousNode = NULL;
        while (currentNode != NULL) {
            if (currentNode->vertex == edge->destinationEdge) {
                if (previousNode == NULL) {
                    graph->adjacentList[edge->sourceEdge] = currentNode->next;
                } else {
                    previousNode->next = currentNode->next;
                }
                free(currentNode);
                graph->numberOfEdges--;
                break;
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }

        // Remove the reverse edge from the destination vertex
        currentNode = graph->adjacentList[edge->destinationEdge];
        previousNode = NULL;
        while (currentNode != NULL) {
            if (currentNode->vertex == edge->sourceEdge) {
                if (previousNode == NULL) {
                    graph->adjacentList[edge->destinationEdge] = currentNode->next;
                } else {
                    previousNode->next = currentNode->next;
                }
                free(currentNode);
                graph->numberOfEdges--;
                break;
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    } else {
        // Invalid edge source or destination
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Print the graph
void printGraphViaAdjacentList(GraphViaAdjacentList* graph) {
    for (unsigned int vertex = 0; vertex < graph->numberOfVertices; vertex++) {
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

// Free the graph memory
void freeGraphViaAdjacentList(GraphViaAdjacentList *graph) {
    for (unsigned int vertex = 0; vertex < graph->numberOfVertices; vertex++) {
        GraphNode* node = graph->adjacentList[vertex];
        while (node != NULL) {
            // Traverse the linked list and free the memory
            GraphNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->adjacentList);
    free(graph);
    printf("Freed the graph memory\n");
}

// Main function
int main(void) {
    // Create a graph with 5 vertices
    GraphViaAdjacentList* graph = createGraphViaAdjacentList(5);

    // Add edges to the graph
    addEdgeToGraphViaAdjacentList(graph, &(Edge){0, 1, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){0, 2, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){1, 2, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){2, 3, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){3, 4, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){4, 0, false});
    addEdgeToGraphViaAdjacentList(graph, &(Edge){0, 5, false});    // Expand the graph to 7 vertices

    // Print the graph
    printGraphViaAdjacentList(graph);
    printf("\n");

    // Remove an edge from the graph
    removeEdgeFromGraphViaAdjacentList(graph, &(Edge){0, 1, false});
    printGraphViaAdjacentList(graph);

    // Free the graph memory
    freeGraphViaAdjacentList(graph);
    
    return 0;
}

// Expanded the graph from 5 to 6 vertices
// Vertex 0 is connected to: 5 4 2 1
// Vertex 1 is connected to: 2 0
// Vertex 2 is connected to: 3 1 0
// Vertex 3 is connected to: 4 2
// Vertex 4 is connected to: 0 3
// Vertex 5 is connected to: 0
// 
// Vertex 0 is connected to: 5 4 2 
// Vertex 1 is connected to: 2
// Vertex 2 is connected to: 3 1 0
// Vertex 3 is connected to: 4 2
// Vertex 4 is connected to: 0 3
// Vertex 5 is connected to: 0
// Freed the graph memory